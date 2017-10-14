#ifndef CANVAS_H
#define CANVAS_H

#include "Core.h"
#include "Fade.h"

namespace Jui
{
	class Canvas : public QWidget
	{
		//Q_OBJECT

	public:
		Canvas();
		Canvas(QWidget *parent = 0);
		Canvas(QWidget *parent, int x, int y, int width, int height);
		Canvas(int x, int y, int width, int height);

		void origin_(int x, int y);
		virtual void geometry_(int x, int y, int w, int h);
		void name_(QString txt);
		
		QPoint origin();
		QString name();
		
		/*
	signals:
		void resized();
		*/
	

	protected:
		//void mousePressEvent(QMouseEvent *e);
		void resizeEvent(QResizeEvent *e) override;
		void paintEvent(QPaintEvent *e) override;
				
	private:
		//FadePoint m_origin;
		void init(int x = 10, int y = 10, int width = 50, int height = 50);
	};
}

#endif // CANVAS_H
