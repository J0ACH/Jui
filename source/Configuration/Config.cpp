#include "Config.h"

namespace Jui
{
	Config::Config(QObject *parent) : QObject(nullptr) { initConfig(100, 100, 500, 500); }
	Config::Config(int x, int y, int w, int h) : QObject(nullptr) { initConfig(x, y, w, h); }

	void Config::initConfig(int x, int y, int w, int h) {

		win = new Win(x, y, w, h);
		win->name_("Configuration");
		
		//Folder f;
		Folder f("c:/test");
		//f.current();
		f.make("test");
		f.enter("test");
		//f.current();
		f.show();

		File txt(f, "pokus.txt");
	}

	void Config::click() {
		//qDebug() << tr("Config::click(%1)").arg(sb->value());
	}
	void Config::result() {
	
	}
}

