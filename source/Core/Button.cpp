#include "Button.h"

namespace Jui
{

	Button::Button(Canvas *parent) : 
		Canvas(parent)
	{
		this->init();
	}
	Button::Button(Canvas *parent, int x, int y, int width, int height) : 
		Canvas(parent, x, y, width, height)
	{
		this->init();
	}
	
	void Button::init()
	{
		connect(
			this, SIGNAL(actMousePressed(Canvas*, QPoint)),
			this, SLOT(onPress())
		);
	}
	
	void Button::onPress() {
		emit actPressed(this);
	}

	void Button::draw() {
		QPainter painter(this);
		painter.setPen(QColor(200, 30, 30));
		painter.drawText(0, 0, this->width(), this->height(), Qt::AlignCenter, this->getName());
	}
	
	Button::~Button()
	{
		qDebug("Button closed");
	}
}

