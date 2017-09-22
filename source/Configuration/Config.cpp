#include "Config.h"

namespace Jui
{
	Config::Config(int x, int y, int width, int height) : Canvas(x, y, width, height)
	{
		Header *configHeader = new Header(this);
		Edges *configEdges = new Edges(this);
		Button *configClose = new Button(configHeader);
		configClose->setGeometry(this->width() - 25, 5, 20, 20);
		configClose->setText("X");
		configClose->colorFrame_(QColor(0, 0, 0, 0), QColor(90, 90, 90));
		connect(
			configClose, SIGNAL(pressed()),
			this, SLOT(close())
		);

		Canvas *test = new Canvas(this, 50, 50, 200, 200);
		Header *testHeader = new Header(test);
		Edges *testEdges = new Edges(test);
				
		Text *t1 = new Text(test);
		t1->setGeometry(40, 80, 50, 20);
		t1->setText("ahoj");
	}
}

