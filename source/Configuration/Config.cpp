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

	class RedWin : public Win {
	public:
		void paintEvent(QPaintEvent *e) {
			QPainter painter(this);
			QRect frameRect = QRect(0, 0, width() - 1, height() - 1);
			QRect fillRect = QRect(0, 0, width(), height());

			painter.fillRect(fillRect, QColor(220, 20, 20));
			painter.setPen(QColor(50, 50, 50));
			painter.drawRect(frameRect);
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

		Win* w = new Win(250, 250, 300, 300);
		Win* w2 = new Win(w);
		//RedWin* w3 = new RedWin();

		
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

