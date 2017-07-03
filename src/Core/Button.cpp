#include "Button.h"

namespace Jui
{

	Button::Button(Canvas *parent, int x, int y, int width, int height) : Canvas(parent, x, y, width, height)
	{
		qDebug("Button new x, y, w, h");
		//this->setBackgroundColor(250, 30, 30);
	}


	void Button::paintEvent(QPaintEvent *event)
	{
		Canvas::paintEvent(event);

		QPainter painter(this);

		painter.setPen(QColor(200,30,30));
		painter.drawText(0, 0, this->width(), this->height(), Qt::AlignCenter, this->getName());
		//painter.stroke();
	}

	Button::~Button()
	{
		qDebug("Button closed");
	}
}

