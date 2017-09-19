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

		LayerPlocha* L2 = new LayerPlocha();
		L2->name_("plocha");
		//L2->alpha_(0.5);

		testButton->addLayer(L2);
		testButton->addLayer(L3);

		Button2* B1 = new Button2(this);
		B1->setGeometry(100, 50, 50, 30);
		B1->setText("B1");
		B1->show();

		/*
		QPropertyAnimation *anim = new QPropertyAnimation(B1, "colorFrame");
		anim->setStartValue(QColor(30, 30, 30));
		anim->setEndValue(QColor(250, 0, 0));
		anim->setDuration(10000);

		anim->start();
		*/


		/*
		Button2* B2 = new Button2(this);
		B2->setGeometry(175, 50, 50, 30);
		B2->setText("B2");
		B2->setFlat(true);
		B2->show();
		*/


		QPushButton* B2 = new QPushButton(this);
		B2->setGeometry(175, 50, 50, 30);
		B2->setText("B2");
		B2->show();

		QStateMachine machine;
		QState *s1 = new QState();
		QState *s2 = new QState();
		QState *s3 = new QState();

		s1->addTransition(B2, SIGNAL(clicked()), s2);
		s2->addTransition(B2, SIGNAL(clicked()), s3);
		s3->addTransition(B2, SIGNAL(clicked()), s1);

		machine.addState(s1);
		machine.addState(s2);
		machine.addState(s3);
		machine.setInitialState(s1);

		s1->assignProperty(B2, "text", "In state s1");
		s2->assignProperty(B2, "text", "In state s2");
		s3->assignProperty(B2, "text", "In state s3");

		machine.start();
/*
		QStateMachine *machine = new QStateMachine;

		QState *state1 = new QState(machine);
		state1->assignProperty(B2, "colorFrame", QColor(30, 30, 30));
		machine->setInitialState(state1);

		QState *state2 = new QState(machine);
		state2->assignProperty(B2, "colorFrame", QColor(230, 30, 30));

		QSignalTransition *transition1 = state1->addTransition(B2, SIGNAL(clicked()), state2);
		transition1->addAnimation(new QPropertyAnimation(B2, "colorFrame"));

		QSignalTransition *transition2 = state2->addTransition(B2, SIGNAL(clicked()), state1);
		transition2->addAnimation(new QPropertyAnimation(B2, "colorFrame"));


		machine->start();
*/
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

