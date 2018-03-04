#ifndef CONFIG_H
#define CONFIG_H

#include "Core.h"
#include "Screens.h"
#include "Fade.h"
#include "Text.h"
#include "Dummies.h"
#include "Button.h"
#include "Geometry.h"
#include "GraphicObjects.h"
#include "Files.h"

#include "Variables.h"

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
		Button *butt;
		Vbool *var;
		//QString testBool;

		void initConfig(int x, int y, int w, int h);

		private slots:
		void click();
		void result();
	};

	
}

#endif // CONFIG_H