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

		//Path path;
		//Path path("temp");
		//Path path("home", "ahoj", "ahoj", "mozna", "nevim", "zase");
		//Path path({"root", "mozna", "nevim", "zase" });
		Path path = Path::disk().add("testFolder");
		File::make(path);
		File::show(path);

		File file(path, "dataTest");

		//Path dir = Path::root() + Path("lide");
		Path dirMuzi = Path("lide", "muzi");
		Path dirZeny = Path("lide", "zeny");
		Leaf leaf1(dirZeny, "jmeno1", "Bara");
		Leaf leaf2(dirMuzi, "jmeno1", "Emil");
		Leaf leaf3(dirMuzi, "jmeno2", "Jarda");
		//qDebug() << l1;

		Data d;
		d.add(Path("lide", "zeny", "divky"), "Alva");
		d.add(leaf1);
		d.add(leaf2);
		d.add(leaf3);


		//d.atPath(Path::root());
		//d.atPath(dir);

		Data d2 = d.filter("jmenoA");
		qDebug() << "D2.size:" <<d2.size();
		qDebug() << "D2.isEmpty:" << d2.isEmpty();

		file.write(d2.toString());
		file.show();
	}

	void Config::click() {

	}
	void Config::result() {

	}
}

