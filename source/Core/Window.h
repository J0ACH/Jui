#ifndef WINDOW_H
#define WINDOW_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include "Controls.h"

namespace Jui
{

	// Screen /////////////////////////////////////////////////////

	class Screen : public QWidget
	{
	public:
		Screen(QWidget *parent = 0);

	protected:
		void paintEvent(QPaintEvent *e) override;
	};

	// Window /////////////////////////////////////////////////////

	class Window : public QMainWindow
	{
		Q_OBJECT

	public:
		Window(QWidget *parent = 0);
		Window(int width, int height);

		void setHeaderWidth(int width);
		void setTitle(QString txt);

	protected:
		void mousePressEvent(QMouseEvent *e) override;
		void mouseMoveEvent(QMouseEvent *e) override;
		void mouseReleaseEvent(QMouseEvent *e) override;
		void resizeEvent(QResizeEvent *e) override;
		void paintEvent(QPaintEvent *e) override;

	private:
		Screen *scr;
		QRect headerRect;
		QLabel *title;
		//WindowButton *closeButton;
		Button *closeButton;
		QPoint mousePressedGlobalCoor, mousePressedOriginCoor;
		bool isMoving;

		void init(int w, int h);

	};

}

#endif // WINDOW_H