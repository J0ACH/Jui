
#include "Config.h"

namespace Jui
{		
	Config::Config(int x, int y, int width, int height) : QWidget()
		//(x, y, width, height)
	{
		qDebug("Config new x, y, w, h, ");

		Canvas *win = new Canvas(700, 100, 400, 400);
		win->setFrameColor(255, 0, 0);
		
		Canvas *test = new Canvas(win, 100, 100, 50, 50);
		test->setName("test");
		test->setBackgroundAlpha(200);
		test->setBackgroundColor(150, 30, 30);
		
		//QObject::connect(test, &Canvas::actMousePressed, win, &Canvas::onClose);
		
		/*
		connect(
		sender, &Sender::valueChanged,
		receiver, &Receiver::updateValue
		);
		*/
	}
		

	Config::~Config()
	{
		qDebug("Config closed");
		//emit actClosed(this);
		//emit actClosed();
	}
}

