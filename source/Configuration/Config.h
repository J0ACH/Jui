#ifndef CONFIG_H
#define CONFIG_H

#include "Core.h"
#include "Fade.h"
#include "Text.h"
#include "Canvas.h"
#include "Dummies.h"
#include "Button.h"
#include <QDebug>

namespace Jui
{
	class Config : public Canvas
	{
		Q_OBJECT
	public:
		Config(int x, int y, int width, int height);
	private:
		FadeFloat fade;
		PureText *pt;
		LineText *lt;

		private slots:
		void click();
		void result();
	};
}

#endif // CONFIG_H