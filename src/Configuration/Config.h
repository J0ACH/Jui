#ifndef CONFIG_H
#define CONFIG_H

//#include <QWidget>
//#include <QDebug>
#include "Canvas.h"

namespace Jui
{
	//class Config : public QWidget
	class Config : public Canvas
	{
		//Q_OBJECT

	public:
		Config(QWidget *parent);
		Config(int x, int y, int width, int height);
		~Config();
	};
}

#endif // CONFIG_H