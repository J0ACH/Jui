#include "Config.h"

namespace Jui
{
	class LayerTest : public Layer
	{
	public:
		void draw(QPainter *painter, QRect bounds) override
		{
			painter->setPen(QColor(230, 30, 30));
			painter->drawLine(0, 0, 25, 25);
		}
	};

	class LayerPlocha : public Layer
	{
	public:
		void draw(QPainter *painter, QRect bounds) override
		{
			painter->fillRect(QRect(0, 0, 20, 20), QColor(30, 100, 30));
		}
	};

	Config::Config(int x, int y, int width, int height) : Canvas2(x, y, width, height)
	{
		Header *configHeader = new Header(this);
		Edges2 *configEdges = new Edges2(this);

		Canvas2 *test = new Canvas2(this, 50, 50, 100, 100);
		Header *testHeader = new Header(test);
		Edges2 *testEdges = new Edges2(test);

		Button *b1 = new Button(test);
		b1->setGeometry(40, 40, 50, 30);
		b1->show();
		
		Text *t1 = new Text(test);
		t1->setGeometry(40, 80, 50, 20);
		t1->setText("ahoj");

	}

}

