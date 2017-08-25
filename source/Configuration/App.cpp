#include <QApplication>
#include "Config.h"


using namespace Jui;

int main(int argc, char** argv) 
{
	QApplication app(argc, argv);	
	Config winConfig(500, 500, 500, 500);
	
	return app.exec();
}

