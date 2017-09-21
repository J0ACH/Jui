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
		Header2 *configHeader = new Header2(this);

		Canvas2 *test = new Canvas2(this, 50, 50, 100, 100);
		Header2 *testHeader = new Header2(test);
		
		Button *b1 = new Button(test);
		b1->setGeometry(40, 40, 50, 30);
		b1->show();
		
		Text *t1 = new Text(test);
		t1->setGeometry(40, 80, 50, 20);
		t1->setText("ahoj");


		/*
		//this->setName("Configuration");
		//this->setBackgroundColor(20, 20, 20);
		//this->setBackgroundAlpha(0);

		HeaderWindow *headerWindow = new HeaderWindow(this);
		Edges *e1 = new Edges(this);

		Canvas *test = new Canvas(this, 100, 100, 200, 200);
		test->setName("test");
		HeaderDialog *headerTest = new HeaderDialog(test);
		Edges *e2 = new Edges(test);

		Button *testButton = new Button(test, 50, 50, 25, 25);
		testButton->addState("A");
		testButton->addState("B");
		testButton->addState("C");
		testButton->addState("D");
		testButton->setStateCounter(1);

		LayerTest* L3 = new LayerTest();
		L3->name_("cara");

		LayerPlocha* L2 = new LayerPlocha();
		L2->name_("plocha");
		//L2->alpha_(0.5);

		testButton->addLayer(L2);
		testButton->addLayer(L3);

		Button2* B1 = new Button2(this);
		B1->setGeometry(100, 50, 50, 30);
		B1->setText("B1");
		B1->show();

		//QPushButton* B2 = new QPushButton(this);
		Button2* B2 = new Button2(this);
		B2->setGeometry(175, 50, 50, 30);
		B2->setText("B2");
		B2->setCheckable(true);
		B2->show();
		B2->setFont(QFont("Consolas", 8));
		//B2->setIcon(QIcon(":/close16.png"));

		QPixmap pixmap(":/close16.png");
		QIcon ButtonIcon(pixmap);
		B2->setIcon(ButtonIcon);
		B2->setIconSize(pixmap.rect().size());


		//QImage(":/close16.png")

		Canvas2* w = new Canvas2(250, 250, 300, 300);
		Canvas2* w2 = new Canvas2(w);
		//RedWin* w3 = new RedWin();
		*/

		
	}

}

