#include "Config.h"

namespace Jui
{
	Config::Config(QObject *parent) : QObject(nullptr) { initConfig(100, 100, 500, 500); }
	Config::Config(int x, int y, int w, int h) : QObject(nullptr) { initConfig(x, y, w, h); }

	void Config::initConfig(int x, int y, int w, int h) {

		win = new Win(x, y, w, h);
		win->name_("Configuration");

		Data dataWrite;
		dataWrite.add("name", "Jachym");
		dataWrite.add("surname", "Pesek");
		dataWrite.add("age", 32);
		dataWrite.add("thickness", 1.2);
		dataWrite.add("color", QColor(30, 40, 60));
		dataWrite.add("font", QFont("TeutonHell", 14));
		dataWrite.add("bool", true);

		Data color;
		color.add("c1", 120);
		color.add("c2", 30);
		color.add("c3", QColor(30, 40, 50));
		dataWrite.add("colorNew", color);

		QMap<QString, QVariant> map;
		map.insert("red", 120);
		map.insert("green", 30);
		map.insert("blue", 30);
		map.insert("alpha2", 255);

		dataWrite.add("mapColor", map);

		dataWrite.print();

		File txt("test.txt");
		txt.write(dataWrite);
		txt.show();

		/*
		File file("test.txt");
		QString txt = dataWrite;
		file.write(txt);
		*/
		//qDebug() << txt;

		/*
		//Folder f;

		//f.show();
		//f.current();
		//f.make("test");
		//f.enter("test");
		//f.current();

		Folder f("c:/test");
		//File txt("c:/test/mozna","pokus.txt");





	//	d.print();

		//Data d2;

		txt.show();
		*/
	}

	void Config::click() {
		//qDebug() << tr("Config::click(%1)").arg(sb->value());
	}
	void Config::result() {

	}
}

