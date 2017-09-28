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
		/*
		Canvas *test = new Canvas(this, 50, 50, 200, 200);
		Header *testHeader = new Header(test);
		Edges *testEdges = new Edges(test);

		Text *t1 = new Text(test);
		t1->setGeometry(40, 80, 50, 20);
		t1->setText("ahoj");
		*/

		//a = new FadeVariable();
		//qDebug() << tr("a.value = %1").arg(a.value());
		//a.value_(10, 10000);
		//a.reciever(this, "result");
		//a.target2(result());


		eText = new TextEdit(this);
		eText->setGeometry(230, 30, 50, 25);

		text = new QLineEdit(this);
		text->setGeometry(130, 30, 50, 25);
		text->show();

		label = new Text(this);
		label->setGeometry(130, 60, 50, 25);
		label->colorText_(100, 30, 30);
		//fade.target(this, &Config::result);
		fade.reciever(this, "result");
		fade.value_(10, 2);

		Button *b = new Button(this);
		b->setGeometry(30, 30, 50, 50);
		connect(
			b, SIGNAL(pressed()),
			this, SLOT(click())
		);

	}

	void Config::click() {
		//qDebug() << tr("Config::click(%1)").arg(text->text());
		fade.value_(text->text().toFloat(), 3);
		label->text_(QString::number(fade.value()));
	}
	void Config::result() {
		label->text_(QString::number(fade.value()));
		//qDebug() << tr("vysledek = %1").arg(QString::number(fade.value()));
	}
}

