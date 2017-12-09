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

		Path dir = Path::root() + Path("lide");
		Leaf leaf1(dir, "jmenoA", "Bara");
		Leaf leaf2(dir, "jmeno1", "Emil");
		Leaf leaf3(dir, "jmeno2", "Jarda");
		//qDebug() << l1;

		Data d;
		d.add(Path::root(), "jmenoA", "Alva");
		d.add(leaf1);
		d.add(leaf2);
		d.add(leaf3);

		file.write(d.toString());
		file.show();

		//d.atPath(Path::root());
		//d.atPath(dir);

		d.filter("jmenoA");
	}

	void Config::click() {

	}
	void Config::result() {

	}
}

