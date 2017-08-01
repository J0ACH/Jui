#include <QApplication>
#include "Config.h"

using namespace Jui;

int main(int argc, char** argv) 
{
	QApplication app(argc, argv);
	
	
	Config winConfig(500, 100, 500, 500);
	//Config conf(0);

	return app.exec();
}

