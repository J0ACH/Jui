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
		QPoint mousePressedParentCoor, mousePressedGlobalCoor, mousePressedLocalCoor;
	};

	class Edge : public QObject
	{
		Q_OBJECT

	public:
		Edge(Canvas *parent);
		~Edge();

		enum direction { Right, Bottom, Left, Top };

		void setDirection(Edge::direction dir, bool visibilty);

	public slots:
		void onMousePress(Canvas*, QPoint);
		void onMouseMoved(Canvas*, QPoint);
		void onParentResize(Canvas*, QSize);

	signals:
		void actResized(QSize size);

	private:
		//void fitPosition();
		Canvas* mParent;
		QMap<Edge::direction, Canvas*> mEdges;
		int thickness, offset, corner, gap;

		QPoint mousePressedParentCoor, mousePressedGlobalCoor, mousePressedLocalCoor;
		QSize mousePressedParentSize;
	};
}

#endif // DUMMY_H