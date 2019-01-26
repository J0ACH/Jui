#include "Console.h"

namespace Jui
{
	Console::Console(QWidget *parent) { this->init(100, 100, 400, 400); }

	void Console::init(int x, int y, int w, int h) {
		setGeometry(x, y, w, h);

		txt = new QLabel(this);
		txt->setGeometry(10, 10, 200, 30);
		txt->setText("aaaaa");
		txt->show();


		show();
	}

	void Console::println(QString msg) {
		txt->setText(msg);
	}
}