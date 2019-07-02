#include <QApplication>
#include "Core.h"
#include "Window.h"
#include "Console.h"
#include "Palette.h"
#include "Screens.h"
#include "Fade.h"
#include "Text.h"
#include "Dummies.h"
#include "Button.h"
#include "Config.h"

using namespace Jui;

#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "user32.lib")

int main(int argc, char** argv) {

	

	QApplication app(argc, argv);

	//Jui::loadFonts();

	Palette style;
	app.setPalette(style.palette());

	Window *win = new Window(600, 600);
	win->setTitle("Main application window");
	//QApplication::setDesktopSettingsAware(false);
	
	/*
	QWidget *widget = new QWidget();
	widget->setGeometry(500, 300, 1000, 1000);
	//widget->setStyleSheet("QWidget { border-top: 1px solid white }");
	widget->show();

	*/

	//MainCanvas* mCanvas = new MainCanvas(20,20,500,500);
	//MainWindow* mWin = new MainWindow(200, 200, 500, 500);
	//GraphicsCanvas gCanvas(600, 300);
	//QGraphicsWidget* wid = new QGraphicsWidget();
	//wid->resize(600, 400);
	//wid->show();
	

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

