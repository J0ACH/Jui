#include "Config.h"

namespace Jui
{
	Config::Config(QObject *parent) : QObject(nullptr) { initConfig(100, 100, 500, 500); }
	Config::Config(int x, int y, int w, int h) : QObject(nullptr) { initConfig(x, y, w, h); }

	void Config::initConfig(int x, int y, int w, int h) {

		win = new Win(x, y, w, h);
		win->name_("Configuration");

		buttBool = new Button(win);
		buttBool->geometry_(20, 100, 30, 35);
		varBool.parent_(win);
		varBool.origin_(100, 100);
		varBool.connectOnChange(this, SLOT(onBoolChange()));
		connect(buttBool, SIGNAL(pressed()), this, SLOT(clickBool()));

		buttInt = new Button(win);
		buttInt->geometry_(20, 150, 30, 35);
		varInt.parent_(win);
		varInt.origin_(100, 150);
		varInt.label_("int");
		varInt.connectOnChange(this, SLOT(onIntChange()));
		connect(buttInt, SIGNAL(pressed()), this, SLOT(clickInt()));

		varIntPlus.parent_(win);
		varIntPlus.origin_(100, 175);
		varIntPlus.label_("plus");

		varString.parent_(win);
		varString.origin_(100, 250);
		varString.label_("str");
		varString.width_(350);
		//varString.text_("test");
	}

	void Config::clickBool() {
		bool b = varBool;
		if (varBool) { varBool = false; }
		else { varBool = true; }
		qDebug() << "Config::clickBool() =" << b << " -> " << varBool;
	}

	void Config::onBoolChange() {
		qDebug() << "Config::onBoolChange";
		varString = QString("Config::onBoolChange() = %1 ").arg(varBool);
	}

	void Config::clickInt() {
		int num = varInt;
		varInt = num + 1;
		qDebug() << "Config::clickInt() =" << num << " -> " << varInt;
	}
	void Config::onIntChange() {
		qDebug() << "Config::onIntChange";
		varIntPlus = varInt + 5;
	}
}

