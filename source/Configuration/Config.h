#ifndef CONFIG_H
#define CONFIG_H

#include "Core.h"
#include "Canvas.h"
#include "Dummy.h"
#include "Button.h"
#include <QLineEdit>


namespace Jui
{
	class Config : public Canvas
	{		
		Q_OBJECT
	public:
		Config(int x, int y, int width, int height);	
		public slots:
		void click();
	private:
		FadeVariable *a;
		QLineEdit *text;
	};
}

#endif // CONFIG_H