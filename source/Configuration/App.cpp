#include <QApplication>
#include "Core.h"
#include "Config.h"

using namespace Jui;

int main(int argc, char** argv) {
	QApplication app(argc, argv);	
	Jui::loadFonts();
	Config winConfig(600, 250, 500, 500);
	
	return app.exec();
}

