#include "Config.h"

namespace Jui
{

	Config::Config(int x, int y, int width, int height) : Canvas(x, y, width, height)
	{
		qDebug("Config new x, y, w, h");

		this->setName("Configuration");
		this->setBackgroundAlpha(0);

		Header *header = new Header(this, 55);

		Button *test = new Button(this, 100, 100, 50, 50);
		test->setName("test");

		Button *test2 = new Button(this, 100, 200, 50, 50);
		test2->setName("test2");
		//test->setBackgroundAlpha(200);
		//test->setBackgroundColor(150, 30, 30);

		Button *closeButton = new Button(header, this->width() - 45, 10, 35, 35);
		closeButton->setName("close");
		//closeButton->setBackgroundColor(250, 30, 30);		

		connect(
			closeButton, SIGNAL(actMousePressed(QPoint, QPoint)),
			this, SLOT(onClose())
		);
	}

	void Config::onPrint()
	{
		qDebug("Config onPrint");
	}

	Config::~Config()
	{
		qDebug("Config closed");
		//emit actClosed(this);
		//emit actClosed();
	}
}

