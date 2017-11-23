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
		//qDebug() << path;
		File::make(path);
		//File::show(path);

		Path dir = Path::root() + Path("lide");

		Leaf l1(dir, "jmeno", "Emil");
		qDebug() << l1;
		//leaf.key_("jmeno").value_("jsemToAAAA").path_(Path::root().add("lide"));
		
		//File f(path, "test");
		//f.write(leaf.toString());
		//f.show();

	}

	void Config::click() {

	}
	void Config::result() {

	}
}

