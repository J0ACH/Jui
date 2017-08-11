#include "Canvas.h"

namespace Jui
{
	Canvas::Canvas(Canvas *parent) : QWidget(parent)
	{
		Canvas::init(0, 0, 100, 100);
		mParent = parent;
		mType = Canvas::type::Panel;
	}

	Canvas::Canvas(Canvas *parent, int x, int y, int width, int height) : QWidget(parent)
	{
		Canvas::init(x, y, width, height);
		mParent = parent;
		mType = Canvas::type::Panel;
	}

	Canvas::Canvas(int x, int y, int width, int height) : QWidget()
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

	Canvas* Canvas::parent() { return mParent; }
	Canvas::type Canvas::getType() { return mType; }
	QPoint Canvas::getOrigin() { return origin; }

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

	void Canvas::connect2(QString signal, Canvas *target, QString slot)
	{
		/*
			connect(
				this, SIGNAL(signal),
				target, SLOT(slot)
			);
		*/


		qDebug("tohle je connect2");
		//qDebug(signal);
	}

	void Canvas::onMousePress(QPoint pt)
	{
		qDebug() << tr("Canvas onMousePress: pt [%1, %2]").arg(
			QString::number(pt.x()),
			QString::number(pt.y())
		);
	}

	void Canvas::onMove(QPoint pt)
	{
		qDebug() << tr("Canvas onMove: pt [%1, %2]").arg(
			QString::number(pt.x()),
			QString::number(pt.y())
		);

		this->setGeometry(
			pt.x(),
			pt.y(),
			this->width(),
			this->height()
		);
	}

	void Canvas::onClose()
	{
		qDebug("Canvas onClose");
		emit actClosed(this);
		this->close();
	}

	void Canvas::mousePressEvent(QMouseEvent *event)
	{
		this->setFocus(Qt::MouseFocusReason);

		QPoint globalPt(event->globalPos().x(), event->globalPos().y());
		QPoint localPt(event->x(), event->y());

		emit actMousePressed(globalPt, localPt);
	}
	void Canvas::mouseMoveEvent(QMouseEvent *event)
	{
		QPoint globalPt(event->globalPos().x(), event->globalPos().y());
		QPoint localPt(event->x(), event->y());

		emit actMouseMoved(globalPt, localPt);
	}
	void Canvas::mouseReleaseEvent(QMouseEvent *event)
	{
		QPoint gPos = event->globalPos();
		qDebug() << tr("MReleased target: %1 [%2, %3]").arg(
			this->name,
			QString::number(gPos.x()),
			QString::number(gPos.y())
		);

		//emit actMousePressed(this, gPos.x(), gPos.y());
		emit actMouseReleased(this, event->x(), event->y());
	}

	void Canvas::focusInEvent(QFocusEvent *event)
	{
		qDebug() << tr("%1 focusInEvent").arg(this->name);
		emit actFocusIn(this);
		this->update();
	}
	void Canvas::focusOutEvent(QFocusEvent *event)
	{
		qDebug() << tr("%1 focusOutEvent").arg(this->name);
		emit actFocusOut(this);
		this->update();
	}

	void Canvas::enterEvent(QEvent *event)
	{
		qDebug() << tr("%1 enterEvent").arg(this->name);
		emit actOverIn(this);
	}
	void Canvas::leaveEvent(QEvent *event)
	{
		qDebug() << tr("%1 leaveEvent").arg(this->name);
		emit actOverOut(this);
	}

	void Canvas::paintEvent(QPaintEvent *event)
	{
		//qDebug() << tr("%1 redraw").arg(this->name);

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
		qDebug("Canvas closed");
		//emit actClosed(this);
		//emit actClosed();
	}

}
