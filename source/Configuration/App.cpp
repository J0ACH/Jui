#include <QApplication>
#include "Core.h"
#include "Console.h"
#include "Screens.h"
#include "Fade.h"
#include "Text.h"
#include "Dummies.h"
#include "Button.h"
#include "Config.h"

using namespace Jui;

int main(int argc, char** argv) {
	
	QApplication app(argc, argv);	
	Jui::loadFonts();
	
	Console a(0);
	a.println("ahoj");

	//Config c(200, 200, 800, 600);
	
	return app.exec();
}
