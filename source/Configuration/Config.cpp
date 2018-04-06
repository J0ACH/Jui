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
		//varBool = new Vbool(win);
		varBool.parent_(win);
		varBool.geometry_(100, 100, 150, 35);
		//varBool->value_(false);
		connect(buttBool, SIGNAL(pressed()), this, SLOT(clickBool()));

		buttInt = new Button(win);
		buttInt->geometry_(20, 150, 30, 35);
		varInt.parent_(win);
		varInt.geometry_(100, 150, 150, 35);
		//varInt = new Vint(win);
		connect(buttInt, SIGNAL(pressed()), this, SLOT(clickInt()));
	}

	void Config::clickBool() {
		bool b = varBool;
		if (varBool) { varBool = false; }
		else { varBool = true; }

		qDebug() << "Config::clickBool() =" << b << " -> " << varBool;
	}

	void Config::clickInt() {
		int num = varInt;
		varInt = num + 1;
		qDebug() << "Config::clickInt() =" << num << " -> " << varInt;
	}
}

