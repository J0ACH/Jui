#ifndef CONFIG_H
#define CONFIG_H

#include "Core.h"
#include "Canvas.h"
#include "Dummies.h"
#include "Button.h"
#include <QLineEdit>


namespace Jui
{
	class Config : public Canvas
	{
		Q_OBJECT
	public:
		Config(int x, int y, int width, int height);
	private:
		FadeVariable a;
		QLineEdit *text;

		private slots:
		void click();
		void result();
	};
}

#endif // CONFIG_H