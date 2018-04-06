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
		Button *buttBool, *buttInt;
		Vbool varBool;
		Vint varInt;
		
		void initConfig(int x, int y, int w, int h);

		private slots:
		void clickBool();
		void clickInt();
		
	};

	
}

#endif // CONFIG_H