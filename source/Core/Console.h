#ifndef CONSOLE_H
#define CONSOLE_H


#include <QtCore>
#include <QtGui>
#include <QtWidgets>

//#include "Core.h"


namespace Jui
{
	class Console : public QWidget
	{
		Q_OBJECT

	public:
		Console(QWidget *parent = 0);
		Console(QWidget *parent, int x, int y, int width, int height);
		Console(int x, int y, int width, int height);

	public slots:
		void println(QString msg);

	protected:
		void resizeEvent(QResizeEvent *e) override;

	private:
		QScrollArea *scroll;

		int size;
		int lineHeight;
		QList<QLabel*> lines;

		void init(int x, int y, int w, int h);


	};

}




#endif // CONSOLE_H