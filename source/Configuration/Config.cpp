#include "Config.h"

namespace Jui
{
	Config::Config(QObject *parent) : QObject(nullptr) { initConfig(100, 100, 500, 500); }
	Config::Config(int x, int y, int w, int h) : QObject(nullptr) { initConfig(x, y, w, h); }

	void Config::initConfig(int x, int y, int w, int h) {

		win = new Win(x, y, w, h);
		win->name_("Configuration");

		Canvas *test = new Canvas(win, 250, 50, 200, 200);
		test->setObjectName("Test");
		Header *testHeader = new Header(test);
		Edges *testEdges = new Edges(test);

		pt = new PureText(test);
		pt->font_("Univers 57 Condensed");
		pt->geometry_(30, 150, 150, 40);
		pt->align_(Qt::AlignLeft | Qt::AlignVCenter);

		Button *b = new Button(win);
		b->setGeometry(30, 50, 50, 50);
		b->pressable_(true);
		b->icon_(":/close16.png", 0);

		connect(
			b, SIGNAL(pressed()),
			this, SLOT(click())
		);

		nb1 = new NumberBox(win);
		nb1->geometry_(30, 90, 200, 80);
		Header *nb1Header = new Header(nb1);

		nb2 = new NumberBox(win);
		nb2->geometry_(30, 200, 200, 80);
		Header *nb2header = new Header(nb2);
		Edges *nb2edges = new Edges(nb2);

		connect(
			nb1, SIGNAL(changed()),
			this, SLOT(result())
		);
		connect(
			nb2, SIGNAL(changed()),
			this, SLOT(result())
		);

		sb = new StringBox(win);
		sb->geometry_(30, 300, 200, 80);
		connect(
			sb, SIGNAL(changed()),
			this, SLOT(click())
		);
		Edges *sbedges = new Edges(sb);
		
		Point *pt = new Point(test);
		pt->x_(test->width() / 2);
		pt->y_(test->height() / 2);

	}

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

