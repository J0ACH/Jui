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

		//a = new FadeVariable();
		a.value_(0);
		//a.target2(result());
		//a.target(this, QMetaMethod(result()));
		a.target(this, "result");
		//a.target(this, result());
		//qDebug() << tr("vysledek = %1").arg(QString::number(a.value()));

		text = new QLineEdit(this);
		text->setGeometry(130, 30, 50, 50);
		text->show();

		Button *b = new Button(this);
		b->setGeometry(30, 30, 50, 50);
		connect(
			b, SIGNAL(pressed()),
			this, SLOT(click())
		);		
	}

	void Config::click() {
		a.value_(text->text().toDouble(), 500);
		//qDebug() << tr("vysledek = %1").arg(QString::number(a->value()));
	}
	void Config::result() {
		qDebug() << tr("vysledek = %1").arg(QString::number(a.value()));
	}
}

