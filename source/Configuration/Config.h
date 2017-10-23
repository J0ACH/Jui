#ifndef CONFIG_H
#define CONFIG_H

#include "Core.h"
#include "Screens.h"
#include "Fade.h"
#include "Text.h"
#include "Dummies.h"
#include "Button.h"
#include "Geometry.h"

namespace Jui
{
	class Config : public QObject
	{
		Q_OBJECT

	public:
		Config(QObject *parent = 0);
		Config(int x, int y, int w, int h);
			
	private:
		Win *win;
		NumberBox *nb1, *nb2;
		PureText *pt;
		StringBox *sb;

		void initConfig(int x, int y, int w, int h);

		private slots:
		void click();
		void result();
	};

	
}

#endif // CONFIG_H