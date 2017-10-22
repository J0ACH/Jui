#ifndef CANVAS_H
#define CANVAS_H

#include "Core.h"
#include "Fade.h"

namespace Jui
{
	class Canvas : public QWidget
	{
		Q_OBJECT

	public:
		Canvas(QWidget *parent = 0);
		Canvas(QWidget *parent, int x, int y, int width, int height);
		Canvas(int x, int y, int width, int height);
		~Canvas();

		static bool isCanvasType(const QObject *qObj);

		void origin_(int x, int y);
		void geometry_(int x, int y, int w, int h);
		void name_(QString txt);
		
		QPoint origin();
		QString name();		
		
	signals:
		void resized(QSize size);

	protected:
		//void mousePressEvent(QMouseEvent *e);
		void resizeEvent(QResizeEvent *e) override;
		void paintEvent(QPaintEvent *e) override;
		
		virtual void fit(QSize size);
				
	private:
		//FadePoint m_origin;
		void init(int x = 10, int y = 10, int width = 50, int height = 50);
	};
}

#endif // CANVAS_H
