#include "Config.h"

namespace Jui
{
	ColorTester::ColorTester(QWidget *parent) : QWidget(parent) {
		backG.value_(QColor(255, 30, 30), 16000);
		backG.reciever(this, "update");
		startTime = QTime::currentTime();
		cnt = 0;
	}
	void ColorTester::paintEvent(QPaintEvent *e) {
		QPainter painter(this);
		QRect fillRect = QRect(0, 0, width(), height());
		painter.fillRect(fillRect, backG.value());

		QTime now = QTime::currentTime();
		qDebug() << tr("%1 -> %2 : %3").arg(
			QString::number(cnt),
			QString::number(now.second() - startTime.second()),
			QString::number(now.msec() - startTime.msec())
		);
		cnt++;
	}

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
		a.value_(10, 10000);
		a.reciever(this, "result");
		//a.target2(result());


		text = new QLineEdit(this);
		text->setGeometry(130, 30, 50, 50);
		text->show();

		Button *b = new Button(this);
		b->setGeometry(30, 30, 50, 50);
		connect(
			b, SIGNAL(pressed()),
			this, SLOT(click())
		);

		ColorTester *ct = new ColorTester(this);
		ct->setGeometry(30, 200, 100, 100);
		ct->show();
	}

	void Config::click() {
		a.value_(text->text().toDouble(), 2000);
		//text->setText(QString::number(a.value()));
		//a.stop();
	}
	void Config::result() {
		qDebug() << tr("vysledek = %1").arg(QString::number(a.value()));
	}
}

