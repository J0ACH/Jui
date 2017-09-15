#include "Config.h"

namespace Jui
{
	class LayerTest : public Layer
	{
	public:
		void draw(QPainter &painter) override 
		{
			painter.setPen(QColor(230, 30, 30));
			painter.drawLine(0, 0, 25, 25);
		}
	};	

	class LayerTest2 : public Layer
	{
	public:
		void draw(QPainter &painter) override
		{
			painter.fillRect(QRect(0, 0, 20, 20), QColor(30, 100, 30));
			//painter.setPen(QColor(30, 230, 30));
			//painter.drawLine(25, 0, 0, 25);
		}
	};

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
		
		LayerTest* L3 = new LayerTest();
		L3->name_("cara");
		testButton->addLayer(L3);

		LayerTest2* L2 = new LayerTest2();
		L2->name_("plocha");
		L2->alpha_(0.5);
		testButton->addLayer(L2);

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

