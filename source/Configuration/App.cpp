#include <QApplication>
#include "Core.h"
#include "Canvas.h"
#include "Fade.h"
#include "Text.h"
#include "Dummies.h"
#include "Button.h"

using namespace Jui;

int main(int argc, char** argv) {
	
	QApplication app(argc, argv);	
	Jui::loadFonts();
	
	Canvas *canvas = new Canvas(600, 250, 500, 500);
	canvas->name_("Configuration");

	Header *configHeader = new Header(canvas);
	Edges *configEdges = new Edges(canvas);
	Button *configClose = new Button(configHeader);

	configClose->geometry_(canvas->width() - 25, 5, 20, 20);
	configClose->label_("X");
	configClose->icon_(":/smallClose16.png");
	//configClose->colorFrame_(QColor(0, 0, 0, 0), QColor(90, 90, 90));
	QObject::connect(
		configClose, SIGNAL(pressed()),
		canvas, SLOT(close())
	);

	Button *b1 = new Button(canvas);
	b1->geometry_(30, 100, 50, 30);
	//b1->icon_(QImage(":/close16.png"), 0);

	Button *b2 = new Button(canvas);
	b2->geometry_(90, 100, 50, 30);
	b2->pressable_(true);
	b2->icon_(":/close16.png");
	
	return app.exec();
}
