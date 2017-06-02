
#include <QApplication>
#include "Canvan.h"
//#include "QntConfig.h"

using namespace Jui;
//using namespace ScIDE;

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	//app.setWindowIcon(QIcon("Qnt_AppIcon_16px.ico"));
	//app.setStyle(QStyleFactory::create("Fusion"));
	//app.setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");

	Canvan *win = new Canvan(700, 100, 400, 400);
	win->setFrameColor(255, 0, 0);
	//win.setTitle("JuiPreview");
	//win.setVersion(Qnt_VERSION_MAJOR, Qnt_VERSION_MINOR, Qnt_VERSION_PATCH);
	//win->show();

	Canvan test(win, 100, 100, 50, 50);
	test.setName("test");
	test.setBackgroundAlpha(200);
	test.setBackgroundColor(150, 30, 30);
	//test.show();
	//app.setPalette(darkPalette);
	//win.msgConsole(QString("pre-bridge"));

	//ScBridge bridge;
	//win.msgConsole(QString("bridge"));

	
	return app.exec();
}

