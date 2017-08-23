#include "Config.h"

namespace Jui
{

	Config::Config(int x, int y, int width, int height) : Canvas(x, y, width, height)
	{
		qDebug("Config new x, y, w, h");

		this->setName("Configuration");
		this->setBackgroundAlpha(0);
		
		Header *header = new Header(this, 55);
		Edges *e1 = new Edges(this);
		Button *closeButton = new Button(header, this->width() - 45, 10, 35, 35);
		closeButton->setName("close");
		

		Canvas *test = new Canvas(this, 100, 300, 200, 200);
		test->setName("test");
		Header *headerTest3 = new Header(test, 25);
		Edges *e2 = new Edges(test);

		connect(
			closeButton, SIGNAL(actMousePressed(Canvas*, QPoint)),
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

