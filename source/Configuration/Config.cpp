#include "Config.h"

namespace Jui
{
	Config::Config(QObject *parent) : QObject(nullptr) { initConfig(100, 100, 500, 500); }
	Config::Config(int x, int y, int w, int h) : QObject(nullptr) { initConfig(x, y, w, h); }

	void Config::initConfig(int x, int y, int w, int h) {

		win = new Win(x, y, w, h);
		win->name_("Configuration");

		Button *butt = new Button(win);
		butt->geometry_(20, 100, 30, 35);

		var = new Vbool(win);
		var->geometry_(100, 100, 150, 35);
		var->value_(false);


		connect(butt, SIGNAL(pressed()), this, SLOT(click()));
	}

	void Config::click() {
		/*
		//if (var->value())
		if (var) { var->value_(false); }
		else { 
			var->value_(true); 
			//var = true;
		}
		*/

		bool a = var;
		qDebug() << "Config::click() testBool:" << a;// var->value();
	
	}
	void Config::result() {

	}
}

