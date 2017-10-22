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

	configClose->setGeometry(canvas->width() - 25, 5, 20, 20);
	configClose->setText("X");
	configClose->colorFrame_(QColor(0, 0, 0, 0), QColor(90, 90, 90));
	QObject::connect(
		configClose, SIGNAL(pressed()),
		canvas, SLOT(close())
	);

	Button2 *b2 = new Button2(canvas);
	b2->geometry_(30, 100, 50, 30);
	
	return app.exec();
}

