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
		Canvas *test = new Canvas(this, 250, 50, 200, 200);
		test->setObjectName("Test");
		Header *testHeader = new Header(test);
		Edges *testEdges = new Edges(test);

		pt = new PureText(test);
		pt->font_("Univers 57 Condensed");
		pt->geometry_(30, 150, 150, 40);
		pt->align_(Qt::AlignLeft | Qt::AlignVCenter);
		//pt->displayFrame_(true);



		/*
			connect(
			lt, &LineText::enterPressed,
			this, &Config::click
		);
		*/

		//fade.target(this, &Config::result);
		//fade.reciever(this, "result");
		//fade.value_(10.0, 2.0);

		Button *b = new Button(this);
		b->setGeometry(30, 50, 50, 50);
		b->setCheckable(true);
		b->icon_(QImage(":/close16.png"), 0);
		b->colorBackground_(QColor(40, 40, 40), QColor(120, 30, 30));
		connect(
			b, SIGNAL(pressed()),
			this, SLOT(click())
		);

		nb1 = new NumberBox(this);
		nb1->geometry_(30, 90, 200, 80);
		Header *nb1Header = new Header(nb1);

		nb2 = new NumberBox(this);
		nb2->geometry_(30, 200, 200, 80);
		Header *nb2eader = new Header(nb2);

		connect(
			nb1, SIGNAL(changed()),
			this, SLOT(result())
		);
		connect(
			nb2, SIGNAL(changed()),
			this, SLOT(result())
		);

		lt = new LineText(this);
		lt->font_("Univers Condensed");
		lt->geometry_(30, 300, 350, 90);

		connect(
			lt, SIGNAL(enterPressed()),
			this, SLOT(click())
		);


	}

	void Config::click() {
		//fade.value_(lt->text.toDouble(), 3.0);
		//qDebug() << tr("Config::click(%1)").arg(lt->text);
	}
	void Config::result() {
		//double a = fade;
		//pt->text_(QString::number(a));
		//qDebug() << tr("vysledek = %1").arg(fade);


		double resultValue = nb1->value() + nb2->value();
		pt->text_(QString::number(resultValue));
		qDebug() << tr("Config::result(%1)").arg(QString::number(resultValue));

		//pt->text_(QString::number(fade.value()));
		//qDebug() << tr("vysledek = %1").arg(QString::number(fade.value()));
	}
}

