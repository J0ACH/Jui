#include <QApplication>
#include "Core.h"
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
	
	/*
	Canvas *canvas = new Canvas(600, 250, 500, 500);
	canvas->name_("Configuration");

	Header *configHeader = new Header(canvas);
	Edges *configEdges = new Edges(canvas);
	Button *configClose = new Button(configHeader);

	configClose->geometry_(canvas->width() - 25, 5, 20, 20);
	configClose->label_("X");
	configClose->icon_(":/close16.png"); 
	QObject::connect(
		configClose, SIGNAL(pressed()),
		canvas, SLOT(close())
	);

	Button *b1 = new Button(canvas);
	b1->geometry_(30, 100, 50, 30);
	
	Button *b2 = new Button(canvas);
	b2->geometry_(90, 100, 50, 30);
	b2->pressable_(true);
	b2->icon_(":/smallClose16.png");

	Win *w = new Win(100, 100, 300, 300);
	w->name_("Configuration");
	*/

	Config c(200, 200, 500, 500);
	
	return app.exec();
}
