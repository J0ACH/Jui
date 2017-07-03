#include "Canvas.h"


namespace Jui
{
	Canvas::Canvas(Canvas *parent) : QWidget(parent)
	{
		qDebug("Canvan new parent ");
		Canvas::init(0, 0, 100, 100);
	}

	Canvas::Canvas(Canvas *parent, int x, int y, int width, int height) : QWidget(parent)
	{
		qDebug("Canvan new parent ");
		Canvas::init(x, y, width, height);
	}

	Canvas::Canvas(int x, int y, int width, int height) : QWidget()
	{
		qDebug("Canvan new x, y, w, h, ");
		//this->setWindowTitle("Canvan");

		Canvas::init(x, y, width, height);
	}

	void Canvas::init(int x, int y, int width, int height)
	{
		this->setWindowFlags(Qt::FramelessWindowHint);
		this->setAttribute(Qt::WA_TranslucentBackground);

		this->setGeometry(x, y, width, height);
		this->setName("Canvan");
		this->setBackgroundColor(30, 30, 30);
		this->setBackgroundAlpha(255);
		this->setFrameColor(120, 120, 120);
		this->setFrameAlpha(255);

		this->show();
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

	void Canvas::onClose()
	{
		qDebug("Canvas onClose");
		emit actClosed(this);
		this->close();
	}

	void Canvas::mousePressEvent(QMouseEvent *event)
	{
		this->setFocus(Qt::MouseFocusReason);

		//this->focusWidget();
		QPoint gPos = event->globalPos();
		qDebug() << tr("MPressed target: %1 [%2, %3]").arg(
			this->name,
			QString::number(gPos.x()),
			QString::number(gPos.y())
		);

		//emit actMousePressed(this, gPos.x(), gPos.y());
		emit actMousePressed(this, event->x(), event->y());

		//this->update();
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
		//emit actMouseEntered(this);
		this->update();
	}
	void Canvas::focusOutEvent(QFocusEvent *event)
	{
		qDebug() << tr("%1 focusOutEvent").arg(this->name);
		//emit actMouseLeaved(this);
		this->update();
	}

	void Canvas::enterEvent(QEvent *event)
	{
		qDebug() << tr("%1 enterEvent").arg(this->name);
		emit actMouseEntered(this);
	}
	void Canvas::leaveEvent(QEvent *event)
	{
		qDebug() << tr("%1 leaveEvent").arg(this->name);
		emit actMouseLeaved(this);
	}

	void Canvas::paintEvent(QPaintEvent *event)
	{
		qDebug() << tr("%1 redraw").arg(this->name);

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
