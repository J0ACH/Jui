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
	//Jui::loadFonts();

	QPalette palette;
	palette.setColor(QPalette::Window, QColor(30, 30, 30));
	palette.setColor(QPalette::WindowText, QColor(200, 200, 200));
	//palette.setColor(QPalette::Base, QColor(200, 50, 50));
	//palette.setColor(QPalette::Button, QColor(200, 50, 50));
	   
	app.setPalette(palette);

	Console a;
	a.setGeometry(100, 100, 600, 600);
	a.show();

	for (int i = 0; i < 50; i++) {
		a.println(QString("test_%1").arg(i));
	}
	a.println("ahoj");

	//Config c(200, 200, 800, 600);

	return app.exec();
}
