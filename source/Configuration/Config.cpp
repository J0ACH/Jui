#include "Config.h"

namespace Jui
{
	Config::Config(QObject *parent) : QObject(nullptr) { initConfig(100, 100, 500, 500); }
	Config::Config(int x, int y, int w, int h) : QObject(nullptr) { initConfig(x, y, w, h); }

	void Config::initConfig(int x, int y, int w, int h) {

		win = new Win(x, y, w, h);
		win->name_("Configuration");

		//QStringList pathList = { "ahoj", "mozna", "nevim", "zase" };
		//int test[] = { 1,2,3,5 };
		
		Path path;
		//Path path("temp");
		//Path path("home", "ahoj", "ahoj", "mozna", "nevim", "zase");
		//Path path({"root", "mozna", "nevim", "zase" });
		Path result = Path::disk().add({ "Games", "OpenTTD" });

		path.add("root", "barva");

		//QStringList pathList = path.toList();
		//QStringList pathList = path.toList().filter("a");
		qDebug() << result;
		result.show();

		qDebug() << path;
		//qDebug() << path.del().del().del();
		//qDebug() << path.add("enter").add("jesteeee");
		//qDebug() << result;

		//Path::current().show();
		//result.show();
		//Path::root().show();

	
		//Data dat();
		//dat.add("barva", QColor(30, 40, 60));

		/*
		File txt("test.txt");
		txt.write(dat);
		txt.show();
				*/

				/*
				//Leaf l1("cislo", 1.6);
				Leaf l1("barva", QColor(30, 40, 60));
				l1.level_(2);

				File txt("test.txt");
				txt.write(l1);
				txt.show();

				qDebug() << l1;
				QByteArray ba = txt.read();
				Leaf l2(ba);
				*/

				/*
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
				*/

				/*
				Data newData(txt.read());
				newData.print();
				*/

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

