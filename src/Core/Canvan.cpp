#include "Canvan.h"


namespace Jui
{
	Canvan::Canvan(QWidget *parent) : QWidget(parent)
	{

	}

	Canvan::Canvan(int x, int y, int width, int height)
	{
		qDebug("Canvan new x, y, w, h, ");
		this->setGeometry(x, y, width, height);
		this->setWindowFlags(Qt::FramelessWindowHint);
		this->setWindowTitle("Canvan");
	}

	void Canvan::paintEvent(QPaintEvent *event)
	{
		QPainter painter(this);
		painter.fillRect(QRect(1, 1, width() - 2, height() - 2), QColor(30,30,30));
		painter.setPen(QColor(150, 150, 150));
		painter.drawRect(QRect(0, 0, width() - 1, height() - 1));

		// QToolBar::paintEvent(event);
	}

	Canvan::~Canvan()
	{
		qDebug("Canvan closed");
	}
}
