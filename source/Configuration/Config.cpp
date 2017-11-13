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
		
		//f.show();
		//f.current();
		//f.make("test");
		//f.enter("test");
		//f.current();

		Folder f("c:/test");
		//File txt("c:/test/mozna","pokus.txt");
		File txt("test.txt");
		
		Data dataWrite;
		dataWrite.add("name", "Jachym");
		dataWrite.add("surname", "Pesek");
		dataWrite.add("age", 32);
		dataWrite.add("thickness", 1.2);
		dataWrite.add("color", QColor(30, 40, 60));
		dataWrite.add("font", QFont("TeutonHell",14));

		Data color;
		color.add("red", 120);
		color.add("green", 30);
		color.add("blue", 30);
		color.add("alpha", 255);
		dataWrite.add("colorNew", color);

	//	d.print();
		txt.write(dataWrite);

		//Data d2;

		txt.show();
	}

	void Config::click() {
		//qDebug() << tr("Config::click(%1)").arg(sb->value());
	}
	void Config::result() {
	
	}
}

