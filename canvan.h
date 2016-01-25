#ifndef CANVAN_H
#define CANVAN_H

#include <QtWidgets/QMainWindow>
#include <QDockWidget>
#include <QPushButton>
#include <QTimer>

//#include "console.h"
//#include "button.h"

#include <QDebug>

class Canvan : public QMainWindow
{
	Q_OBJECT

public:
	Canvan(
		int originX = 100,
		int originY = 100,
		int sizeX = 600,
		int sizeY = 400
		);

	~Canvan();
signals:
	void sendToConsole(QString);

	public slots:
	void msgConsole(QString);

	void closeCanvan();
	void minimizeCanvan();
	void maximizeCanvan();

protected:
	void mousePressEvent(QMouseEvent *event);
	void resizeEvent(QResizeEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

private:
	
	QWidget *header;
	QWidget *screen;
	//QStatusBar *tail;

	QPushButton *closeButton;
	QPushButton *maximizeButton;
	QPushButton *minimizeButton;
	//Button *testButton;

	//QDockWidget *dock;
	//Console *console;

	void setPalette();


	QPalette *palette;
	QColor *textColor;
	QColor *activeColor;
	QBrush *backColor;
	QBrush *panelColor;

	QPoint *globalCursor;
	QPoint *mCursor;
};



#endif // CANVAN_H
