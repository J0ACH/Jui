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


	//qDebug() << settings.value;

	
	//Jui::get

	/*
	Console a;
	a.setGeometry(100, 100, 600, 600);

	//Qt::WindowFlags flags = a.windowFlags();
	//flags.setFlag(Qt::WindowMinMaxButtonsHint, false);
	//flags.setFlag(Qt::WindowCloseButtonHint, false);
	//flags.setFlag(Qt::CustomizeWindowHint, true);
	//flags |= Qt::CustomizeWindowHint;
	//flags &= ~Qt::WindowContextHelpButtonHint;
	//flags &= ~Qt::WindowSystemMenuHint;
	//flags &= ~Qt::WindowMinMaxButtonsHint;
	//flags &= ~Qt::WindowCloseButtonHint;
	//a.setWindowFlags(Qt::CustomizeWindowHint);
	//a.setWindowFlags(flags);

	QPixmap pixmap(32, 32);
	pixmap.fill(Qt::transparent);
	a.setWindowIcon(QIcon(pixmap));

	a.setWindowTitle("Console");
	a.show();


	for (int i = 0; i < 50; i++) {
		a.println(QString("test_%1").arg(i));
	}
	a.println("ahoj");
	*/

	//Config c(200, 200, 800, 600);

	//MainCanvas mCanvas(500,500,1000,1000);
	//mCanvas.show();
	QColor activeWinColor = Jui::getWindowsAccentColor();
	qDebug() << "WinColor: " << activeWinColor.red() << ", " << activeWinColor.green() << ", " << activeWinColor.blue();

	Win w(500, 500, 1000, 1000);
	w.name_("Testing window");
	w.colorActive_(activeWinColor);
	//w.show();

	return app.exec();
}
