#ifndef CONSOLE_H
#define CONSOLE_H


#include <QtCore>
#include <QtGui>
#include <QtWidgets>


namespace Jui
{
	class Console : public QWidget
	{
		Q_OBJECT

	public:
		Console(QWidget *parent = 0);

	public slots:
		void println(QString msg);

	private:
		QLabel *txt;

		void init(int x, int y, int w, int h);

	};

}




#endif // CONSOLE_H