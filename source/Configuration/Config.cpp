#include "Config.h"

namespace Jui
{
	Config::Config(QWidget *parent) : QObject(parent) {  }
	Config::Config(int x, int y, int width, int height) : QObject(0)
	{
		canvas = new Canvas(600, 250, 500, 500);
		canvas->name_("Configuration");

		/*
		Header *configHeader = new Header(canvas);
		Edges *configEdges = new Edges(canvas);
		Button *configClose = new Button(configHeader);

		configClose->setGeometry(canvas->width() - 25, 5, 20, 20);
		configClose->setText("X");
		configClose->colorFrame_(QColor(0, 0, 0, 0), QColor(90, 90, 90));
		connect(
			configClose, SIGNAL(pressed()),
			canvas, SLOT(close())
		);

			
		Canvas *test = new Canvas(this, 250, 50, 200, 200);
		test->setObjectName("Test");
		Header *testHeader = new Header(test);
		Edges *testEdges = new Edges(test);

		pt = new PureText(test);
		pt->font_("Univers 57 Condensed");
		pt->geometry_(30, 150, 150, 40);
		pt->align_(Qt::AlignLeft | Qt::AlignVCenter);
		
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

		sb = new StringBox(this);
		sb->geometry_(30, 300, 200, 80);
		connect(
			sb, SIGNAL(changed()),
			this, SLOT(click())
		);
		*/
	}
/*
	void Config::fit(QSize size) {
		qDebug() << tr("Config::fit(%1, %2)").arg(
			QString::number(size.width()),
			QString::number(size.height())
		);
	}
*/

	void Config::click() {
		//qDebug() << tr("Config::click(%1)").arg(sb->value());
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

