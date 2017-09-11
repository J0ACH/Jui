#include "Config.h"

namespace Jui
{

	Config::Config(int x, int y, int width, int height) : Canvas(x, y, width, height)
	{
		this->setName("Configuration");
		this->setBackgroundColor(20, 20, 20);
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

		Layer *L1 = new Layer(test);
		L1->alpha_(0.2);

		Layer *L2 = new Layer(test);
		L2->alpha_(0.8);
		//L1->alpha();
		//Layer::alpha()
		Layer::alpha2(L2);

		Layer::drawTest(L2);
		
	}

	void Layer::drawTest(Layer* l) {
		
		//QPainter painter(l);
		//painter.fillRect(this->bounds(), QColor(200,30,30));
		
	}

	void Config::onPrint()
	{
		qDebug("Config onPrint");
	}

	Config::~Config()
	{
		qDebug("Config closed");
	}
}

