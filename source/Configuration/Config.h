#ifndef CONFIG_H
#define CONFIG_H

#include "Core.h"
#include "Fade.h"
#include "Canvas.h"
#include "Dummies.h"
#include "Button.h"
#include <QLineEdit>
#include <QTime>


namespace Jui
{
	class ColorTester : public QWidget
	{
	public:
		ColorTester(QWidget *parent = 0);
	protected:
		void paintEvent(QPaintEvent *e) override;
	private:
		FColor backG;
		QTime startTime;
		int startSec, startMSec;
	};
	class Config : public Canvas
	{
		Q_OBJECT
	public:
		Config(int x, int y, int width, int height);
	private:
		FDouble a;
		QLineEdit *text;
		QWidget *colorTester;

		private slots:
		void click();
		void result();
	};
}

#endif // CONFIG_H