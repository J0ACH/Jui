#ifndef CONFIG_H
#define CONFIG_H

#include <QWidget>
#include <QDebug>

#include "Canvas.h"

namespace Jui
{
	class Config : public QWidget
	{
		Q_OBJECT

	public:
		Config(int x, int y, int width, int height);
		~Config();
	};
}

#endif // CONFIG_H