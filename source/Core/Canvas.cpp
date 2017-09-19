#include "Canvas.h"

namespace Jui
{
	Canvas::Canvas(Canvas *parent) :
		QWidget(parent)
	{
		Canvas::init(0, 0, 100, 100);
		mParent = parent;
		mType = Canvas::type::Panel;
	}
	Canvas::Canvas(Canvas *parent, int x, int y, int width, int height) :
		QWidget(parent)
	{
		Canvas::init(x, y, width, height);
		mParent = parent;
		mType = Canvas::type::Panel;
	}
	Canvas::Canvas(int x, int y, int width, int height) :
		QWidget(0)
	{
		Canvas::init(x, y, width, height);
		mParent = NULL;
		mType = Canvas::type::Window;
	}

	void Canvas::init(int x, int y, int width, int height)
	{
		//qDebug() << tr("Canvas::init()");

		this->setWindowFlags(Qt::FramelessWindowHint);
		this->setAttribute(Qt::WA_TranslucentBackground);

		origin.setX(x);
		origin.setY(y);

		this->setGeometry(x, y, width, height);
		this->setName("Canvan");

		mState = Canvas::states::normal;

		this->setBackgroundVisible(true);
		this->setBackgroundColor(30, 30, 30);
		this->setBackgroundAlpha(255);

		this->setFrameVisible(true);
		this->setFrameColor(50, 50, 50);
		this->setFrameAlpha(255);

		this->show();
	}

	Canvas* Canvas::getParent() { return mParent; }
	QPoint Canvas::getOrigin() {
		switch (mType)
		{
		case Jui::Canvas::Window:
			return this->mapToGlobal(QPoint(0, 0));
			break;
		case Jui::Canvas::Panel:
			return this->mapToParent(QPoint(0, 0));
			break;
		};
		return QPoint(0, 0);
	}
	QRect Canvas::bounds() { return QRect(0, 0, width() - 1, height() - 1); }
	Canvas::states Canvas::getState() { return mState; }

	void Canvas::setName(QString name) { mName = name; }
	QString Canvas::getName() { return mName; }

	void Canvas::setBackgroundVisible(bool visibility) {
		visibleBackground = visibility;
		this->update();
	}
	void Canvas::setBackgroundAlpha(int alpha) {
		if (alpha < 1) alpha = 1;
		if (alpha > 255) alpha = 255;
		this->colorBackround.setAlpha(alpha);
		//this->update();
	}
	void Canvas::setBackgroundColor(int red, int green, int blue)
	{
		this->colorBackround.setRed(red);
		this->colorBackround.setGreen(green);
		this->colorBackround.setBlue(blue);
		//this->update();
	}

	void Canvas::setFrameVisible(bool visibility) {
		visibleFrame = visibility;
		//if (visibility) { frameVisibility = Canvas::visible::normal; }
		//else { frameVisibility = Canvas::visible::off; }
		this->update();
	}
	void Canvas::setFrameAlpha(int alpha) {
		if (alpha < 1) alpha = 1;
		if (alpha > 255) alpha = 255;
		this->colorFrame.setAlpha(alpha);
		this->update();
	}
	void Canvas::setFrameColor(int red, int green, int blue)
	{
		this->colorFrame.setRed(red);
		this->colorFrame.setGreen(green);
		this->colorFrame.setBlue(blue);
		this->update();
	}

	void Canvas::onClose() { this->close(); }
	void Canvas::setOrigin(QPoint pt) { this->move(pt); }
	void Canvas::setSize(QSize size) { this->resize(size); }

	void Canvas::mousePressEvent(QMouseEvent *event)
	{
		mState = Canvas::states::active;
		this->setFocus(Qt::MouseFocusReason);
		QPoint globalPt(event->globalPos().x(), event->globalPos().y());
		emit actMousePressed(this, globalPt);
		this->update();
	}
	void Canvas::mouseMoveEvent(QMouseEvent *event)
	{
		QPoint globalPt(event->globalPos().x(), event->globalPos().y());
		emit actMouseMoved(this, globalPt);
	}
	void Canvas::mouseReleaseEvent(QMouseEvent *event)
	{
		mState = Canvas::states::over;
		QPoint globalPt(event->globalPos().x(), event->globalPos().y());
		emit actMouseReleased(this, globalPt);
		this->update();
	}

	void Canvas::focusInEvent(QFocusEvent *event)
	{
		emit actFocusIn(this);
	}
	void Canvas::focusOutEvent(QFocusEvent *event)
	{
		emit actFocusOut(this);
	}

	void Canvas::enterEvent(QEvent *event)
	{
		mState = Canvas::states::over;
		emit actOverIn(this);
		this->update();
	}
	void Canvas::leaveEvent(QEvent *event)
	{
		mState = Canvas::states::normal;
		emit actOverOut(this);
		this->update();
	}

	void Canvas::moveEvent(QMoveEvent *event) {
		emit actMoved(this, event->pos());
	}
	void Canvas::resizeEvent(QResizeEvent *event) {
		emit actResized(this, this->size());
	}

	void Canvas::addLayer(Layer* layer) {
		qDebug() << tr("Canvas::addLayer * (%1)").arg(layer->name());
		layers.insert(layer->name(), layer);
		order.append(layer);
	}
	Layer* Canvas::getLayer(QString name) {
		return layers.value(name);
	}

	void Canvas::paintEvent(QPaintEvent *event)
	{
		QPainter painter(this);

		switch (mState)
		{
		case Canvas::states::normal:
			if (visibleBackground) painter.fillRect(this->bounds(), colorBackround);
			painter.setPen(colorFrame);
			if (visibleFrame) painter.drawRect(this->bounds());
			break;
		case Canvas::states::over:
			if (visibleBackground) painter.fillRect(this->bounds(), colorBackround);
			painter.setPen(QColor(130, 130, 130));
			if (visibleFrame) painter.drawRect(this->bounds());
			break;
		case Canvas::states::active:
			if (visibleBackground) painter.fillRect(this->bounds(), colorBackround);
			painter.setPen(QColor(255, 255, 255));
			if (visibleFrame) painter.drawRect(this->bounds());
			break;
		}

		//this->draw(painter);
		//this->draw2(&painter);

		foreach(Layer* oneLayer, order)
		{
			painter.setOpacity(oneLayer->alpha());
			oneLayer->draw(&painter, this->rect());
		};
		
	}

	void Canvas::changed() { }

	/*
	void Canvas::draw(QPainter &painter) {	}
	void Canvas::draw2(QPainter *painter) {  }
	*/

	Canvas::~Canvas()
	{
		emit actClosed(this);
	}

	// Win /////////////////////////////////

	Win::Win(int x, int y, int w, int h) : QWidget(0) {
		setGeometry(x, y, w, h);
		setWindowFlags(Qt::FramelessWindowHint);
		setAttribute(Qt::WA_TranslucentBackground);		
	}

	void Win::paintEvent(QPaintEvent *e) {
		QPainter painter(this);
		QRect frameRect = QRect(0, 0, width() - 1, height() - 1);
		QRect fillRect = QRect(0, 0, width(), height());

		painter.fillRect(fillRect, QColor(20, 20, 20, 1));

		painter.setPen(QColor(50, 50, 50));
		painter.drawRect(frameRect);

		//painter.setPen(QColor(255, 255, 255));
		//painter.drawText(fillRect, Qt::AlignCenter, this->text());
	}

}
