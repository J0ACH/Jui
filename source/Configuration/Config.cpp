#include "Config.h"

namespace Jui
{

	Config::Config(int x, int y, int width, int height) : Canvas(x, y, width, height)
	{
		qDebug("Config new x, y, w, h");

		this->setName("Configuration");
		//this->setBackgroundAlpha(0);
		
		Header *header = new Header(this);
		Edges *e1 = new Edges(this);
					
		Canvas *test = new Canvas(this, 100, 100, 200, 200);
		test->setName("test");
		Header *headerTest = new Header(test);
		Edges *e2 = new Edges(test);

		Button *closeButton = new Button(header, this->width() - 45, 10, 25, 25);
		closeButton->setName("close");

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

