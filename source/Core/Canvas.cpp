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
		this->setWindowFlags(Qt::FramelessWindowHint);
		this->setAttribute(Qt::WA_TranslucentBackground);

		origin.setX(x);
		origin.setY(y);

		this->setGeometry(x, y, width, height);
		this->setName("Canvan");
		this->setBackgroundColor(30, 30, 30);
		this->setBackgroundAlpha(255);
		this->setFrameColor(120, 120, 120);
		this->setFrameAlpha(255);

		this->show();
	}

	Canvas* Canvas::getParent() { return mParent; }
	Canvas::type Canvas::getType() { return mType; }
	QPoint Canvas::getOrigin(bool global) {
		QPoint origin;
		if (global)
		{
			origin = this->mapToGlobal(QPoint(0, 0));
		}
		else
		{
			origin = this->mapToParent(QPoint(0, 0));
		}
		return origin;
	}

	void Canvas::setName(QString name) { this->name = name; }
	QString Canvas::getName() { return name; }

	void Canvas::setBackgroundAlpha(int alpha) {
		if (alpha < 1) alpha = 1;
		if (alpha > 255) alpha = 255;
		this->colorBackround.setAlpha(alpha);
	}
	void Canvas::setBackgroundColor(int red, int green, int blue)
	{
		this->colorBackround.setRed(red);
		this->colorBackround.setGreen(green);
		this->colorBackround.setBlue(blue);
	}

	void Canvas::setFrameAlpha(int alpha) {
		if (alpha < 1) alpha = 1;
		if (alpha > 255) alpha = 255;
		this->colorFrame.setAlpha(alpha);
	}
	void Canvas::setFrameColor(int red, int green, int blue)
	{
		this->colorFrame.setRed(red);
		this->colorFrame.setGreen(green);
		this->colorFrame.setBlue(blue);
	}

	void Canvas::onClose() { this->close(); }
	void Canvas::onMove(QPoint pt)
	{
		QPoint resultPt;
		switch (mType)
		{
		case Jui::Canvas::Window:
			resultPt = pt;
			this->move(resultPt);
			origin = resultPt;
			break;
		case Jui::Canvas::Panel:
			resultPt.setX(0);; //pt.x() - this->getOrigin(false).x());
			//resultPt.setY(pt.y() - this->getOrigin(true).y());
			resultPt = pt;
			this->move(resultPt);
			origin = resultPt;
			break;
		default:
			break;
		};		

		qDebug() << tr("Canvas onMove: pt [%1, %2]").arg(
			QString::number(resultPt.x()),
			QString::number(resultPt.y())
		);		
	}
	void Canvas::setSize(QSize size) {
		this->resize(size); 
		emit actResized(this, this->size());
	}

	void Canvas::mousePressEvent(QMouseEvent *event)
	{
		this->setFocus(Qt::MouseFocusReason);
		QPoint globalPt(event->globalPos().x(), event->globalPos().y());
		emit actMousePressed(this, globalPt);
	}
	void Canvas::mouseMoveEvent(QMouseEvent *event)
	{
		QPoint globalPt(event->globalPos().x(), event->globalPos().y());
		emit actMouseMoved(this, globalPt);
	}
	void Canvas::mouseReleaseEvent(QMouseEvent *event)
	{
		QPoint globalPt(event->globalPos().x(), event->globalPos().y());
		emit actMouseReleased(this, globalPt);
	}

	void Canvas::focusInEvent(QFocusEvent *event)
	{
		emit actFocusIn(this);
		this->update();
	}
	void Canvas::focusOutEvent(QFocusEvent *event)
	{
		emit actFocusOut(this);
		this->update();
	}

	void Canvas::enterEvent(QEvent *event)
	{
		emit actOverIn(this);
		this->update();
	}
	void Canvas::leaveEvent(QEvent *event)
	{
		emit actOverOut(this);
		this->update();
	}

	void Canvas::paintEvent(QPaintEvent *event)
	{
		QPainter painter(this);
		QColor colFrame, colBackg;

		if (this->hasFocus())
		{
			colFrame = QColor(255, 255, 255);
			colBackg = QColor(
				this->colorBackround.red(),
				this->colorBackround.green(),
				this->colorBackround.blue(),
				200
			);
		}
		else {
			colFrame = this->colorFrame;
			colBackg = this->colorBackround;
		}

		painter.fillRect(QRect(0, 0, width(), height()), colBackg);
		painter.setPen(colFrame);
		painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
	}

	Canvas::~Canvas()
	{
		emit actClosed(this);
	}

}
