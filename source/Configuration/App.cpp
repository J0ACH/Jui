#include <QApplication>
#include "Core.h"
#include "Console.h"
#include "Palette.h"
#include "Screens.h"
#include "Fade.h"
#include "Text.h"
#include "Dummies.h"
#include "Button.h"
#include "Config.h"

using namespace Jui;

int main(int argc, char** argv) {




	//QApplication::setDesktopSettingsAware(false);
	QApplication app(argc, argv);
	
	//Jui::loadFonts();
	
	Palette style;
	app.setPalette(style.palette());

	/*
	QWidget *widget = new QWidget();
	widget->setGeometry(500, 300, 1000, 1000);
	//widget->setStyleSheet("QWidget { border-top: 1px solid white }");
	widget->show();

	*/

	MainCanvas* mCanvas = new MainCanvas(20,20,500,500);
	//MainWindow* mWin = new MainWindow(20, 20, 500, 500);

	/*
	Win *w = new Win(1600, 300, 1000, 1000);
	w->name_("Testing window");
	w->show();
	*/

	/*
	Win *win = new Win(500, 500, 1000, 1000);
	win->name_("Console");

	Console console(win->widget(), 5, 10, win->width() - 10, win->height() - 50);
	console.show();

	for (int i = 0; i < 50; i++) {
		console.println(QString("Console_%1").arg(i));
	}
	console.println("ahoj");
	*/

	//Config c(200, 200, 800, 600);


	return app.exec();
}
