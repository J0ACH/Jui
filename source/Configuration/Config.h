#ifndef CONFIG_H
#define CONFIG_H

#include "Core.h"
#include "Canvas.h"
#include "Fade.h"
#include "Text.h"
#include "Dummies.h"
#include "Button.h"

//#include <QDebug>
//#include <QMetaObject>

namespace Jui
{
	class Config : public QObject
	{
		Q_OBJECT

	public:
		Config(QWidget *parent = 0);
		Config(int x, int y, int width, int height);

	//	void fit(QSize size) override;
	
	private:
		Canvas *canvas;
		NumberBox *nb1, *nb2;
		PureText *pt;
		StringBox *sb;

		private slots:
		void click();
		void result();
	};

	
}

#endif // CONFIG_H