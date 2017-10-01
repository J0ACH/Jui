#ifndef CONFIG_H
#define CONFIG_H

#include "Core.h"
#include "Fade.h"
#include "Canvas.h"
#include "Dummies.h"
#include "Button.h"
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTime>
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
		//FadeInt fade;
		//QLineEdit *text;
		Text *label;
		TextEdit *eText;
		
		private slots:
		void click();
		void result();
	};
}

#endif // CONFIG_H