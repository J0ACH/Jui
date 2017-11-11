#include "Config.h"

namespace Jui
{
	Config::Config(QObject *parent) : QObject(nullptr) { initConfig(100, 100, 500, 500); }
	Config::Config(int x, int y, int w, int h) : QObject(nullptr) { initConfig(x, y, w, h); }

	void Config::initConfig(int x, int y, int w, int h) {

		win = new Win(x, y, w, h);
		win->name_("Configuration");
		
		/*
		*/
		//Folder f;
		//Folder f("c:/test");
		//f.show();
		//f.current();
		//f.make("test");
		//f.enter("test");
		//f.current();

		//File txt(f, "pokus.txt");
		File txt("test.txt");
		
		Data d;
		d.add("name", "Jachym");
		d.add("surname", "Pesek");
		d.add("age", 32);
		d.add("color", QColor(30, 40, 60));
		d.print();
		txt.write(d);

		
	}

	void Config::click() {
		//qDebug() << tr("Config::click(%1)").arg(sb->value());
	}
	void Config::result() {
	
	}
}

