#include "Canvan.h"


namespace Jui
{

	Canvan::Canvan(QWidget *parent, int x, int y, int width, int height) : QWidget(parent)
	{
		qDebug("Canvan new parent ");
		Canvan::init(x, y, width, height);
	}

	Canvan::Canvan(int x, int y, int width, int height) : QWidget(0)
	{
		qDebug("Canvan new x, y, w, h, ");
		//this->setWindowTitle("Canvan");

		Canvan::init(x, y, width, height);
	}

	void Canvan::init(int x, int y, int width, int height)
	{
		this->setWindowFlags(Qt::FramelessWindowHint);
		this->setAttribute(Qt::WA_TranslucentBackground);

		this->setGeometry(x, y, width, height);
		this->setName("Canvan");
		this->setBackgroundColor(30, 30, 30);
		this->setBackgroundAlpha(0);
		this->setFrameColor(120, 120, 120);
		this->setFrameAlpha(255);

		this->show();
	}

	void Canvan::setName(QString name) { this->name = name; }

	void Canvan::setBackgroundAlpha(int alpha) {
		if (alpha < 1) alpha = 1;
		if (alpha > 255) alpha = 255;		
		this->colorBackround.setAlpha(alpha);
	}
	void Canvan::setBackgroundColor(int red, int green, int blue)
	{
		this->colorBackround.setRed(red);
		this->colorBackround.setGreen(green);
		this->colorBackround.setBlue(blue);
	}
	
	void Canvan::setFrameAlpha(int alpha) {
		if (alpha < 1) alpha = 1;
		if (alpha > 255) alpha = 255;
		this->colorFrame.setAlpha(alpha);
	}
	void Canvan::setFrameColor(int red, int green, int blue)
	{
		this->colorFrame.setRed(red);
		this->colorFrame.setGreen(green);
		this->colorFrame.setBlue(blue);
	}


	void Canvan::mousePressEvent(QMouseEvent *mouseEvent)
	{
		QPoint gPos = mouseEvent->globalPos();
		//QPoint *mCursorGlobal = new QPoint(&mouseEvent->globalPos()));
		//QPoint *mCursorLocal = event->pos();
		qDebug("Canvan mouse pressed event");

		qDebug()
			<< "Name:" << this->name
			<< "gPosX:" << gPos.x()
			<< "gPosY:" << gPos.y();
		
		//emit actMousePressed(this, gPos.x(), gPos.y());
		//emit actMousePressed();
	}

	void Canvan::paintEvent(QPaintEvent *event)
	{
		QPainter painter(this);
		painter.fillRect(QRect(0, 0, width(), height()), this->colorBackround);
		painter.setPen(this->colorFrame);
		painter.drawRect(QRect(0, 0, width() - 1, height() - 1));

		// QToolBar::paintEvent(event);
	}

	Canvan::~Canvan()
	{
		qDebug("Canvan closed");
		//emit actClosed(this);
		//emit actClosed();
	}
}
