#include "Config.h"

namespace Jui
{
	Config::Config(int x, int y, int width, int height) : Canvas(x, y, width, height)
	{
		this->setObjectName("Configuration");
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
		/*
		Canvas *test = new Canvas(this, 50, 50, 200, 200);
		Header *testHeader = new Header(test);
		Edges *testEdges = new Edges(test);
		*/

		pt = new PureText(this);
		pt->font_("Consolas");
		pt->geometry_(30, 200, 150, 40);
		pt->displayFrame_(true);

		lt = new LineText(this);
		lt->font_("Univers Condensed");
		lt->geometry_(30, 250, 350, 90);

		connect(
			lt, SIGNAL(enterPressed()),
			this, SLOT(click())
		);

		/*
			connect(
			lt, &LineText::enterPressed,
			this, &Config::click
		);
		*/


		//fade.target(this, &Config::result);
		fade.reciever(this, "result");
		fade.value_(10, 2);
		
		Button *b = new Button(this);
		b->setGeometry(30, 50, 50, 50);
		b->setCheckable(true);
		connect(
			b, SIGNAL(pressed()),
			this, SLOT(click())
		);


	}

	void Config::click() {
		qDebug() << tr("Config::click(%1)").arg(lt->text);
		fade.value_(lt->text.toFloat(), 3);
		//pt->text_(QString::number(fade.value()));
	}
	void Config::result() {
		pt->text_(QString::number(fade.value()));
		//qDebug() << tr("vysledek = %1").arg(QString::number(fade.value()));
	}
}

