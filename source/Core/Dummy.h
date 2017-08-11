#ifndef DUMMY_H
#define DUMMY_H

#include "Canvas.h"

namespace Jui
{
	class Header : public Canvas
	{
		Q_OBJECT

	public:
		Header(Canvas *parent, int height);
		~Header();

	signals:
		void actMoved(QPoint pt);

	protected:
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void paintEvent(QPaintEvent *event);

	private:

		

		QPoint lastPressedMousePosition, temp;
		QRect temp2;
	};

}

#endif // DUMMY_H