#include "Config.h"

namespace Jui
{
	Config::Config(QObject *parent) : QObject(nullptr) { initConfig(100, 100, 500, 500); }
	Config::Config(int x, int y, int w, int h) : QObject(nullptr) { initConfig(x, y, w, h); }

	void Config::initConfig(int x, int y, int w, int h) {

		win = new Win(x, y, w, h);
		win->name_("Configuration");

		/*
		QMap<QString, QVariant> map;
		map.insert("red", 120);
		map.insert("green", 30);
		map.insert("blue", 30);
		map.insert("alpha", 255);

		Node n("test", map);
		QByteArray ba = n;
		qDebug() << "ba:" << ba;
		*/

		Data dataWrite;
		dataWrite.add("name", "Jachym");
		dataWrite.add("surname", "Pesek");
		dataWrite.add("age", 32);
		dataWrite.add("thickness", 1.2);
		//dataWrite.add("color", 30, 40, 60);
		//	dataWrite.add("font", QFont("TeutonHell", 14));

		Data color;
		color.add("c1", 120);
		color.add("c2", 30);
		color.add("c3", 30, 40, 50);
		dataWrite.add("colorNew", color);
		/*

		dataWrite.print();
		
		File txt("test.txt");
		txt.write(dataWrite);
		txt.show();
		*/

		File file("test.txt");
		QString txt = dataWrite;
		file.write(txt);
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

