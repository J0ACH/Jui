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
		mSwitch = Button::stateSwitch::off;

		connect(
			this, SIGNAL(actMousePressed(Canvas*, QPoint)),
			this, SLOT(onPress())
		);
	}

	void Button::onPress() {
		switch (mSwitch)
		{
		case Button::stateSwitch::on:
			mSwitch = Button::stateSwitch::off;
			break;
		case Button::stateSwitch::off:
			mSwitch = Button::stateSwitch::on;
			break;
		}
		emit actPressed(this);
	}

	void Button::draw() {
		QPainter painter(this);

		switch (mSwitch)
		{
		case Button::stateSwitch::on:
			painter.fillRect(QRect(1, 1, width() - 2, height() - 2), QColor(120, 30, 30));
			break;
		case Button::stateSwitch::off:
			break;
		}

		painter.setPen(QColor(200, 30, 30));
		painter.drawText(0, 0, this->width(), this->height(), Qt::AlignCenter, this->getName());
	}

	Button::~Button()
	{
		qDebug("Button closed");
	}
}

