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

	class EdgeControler : public Canvas
	{
		Q_OBJECT

	public:
		enum direction { Right, Bottom, Left, Top };

		//EdgeControler(Canvas* parent, EdgeControler::direction dir);
		//EdgeControler(Edges* parent, EdgeControler::direction dir);
		EdgeControler(Canvas* parent, QObject* edges, EdgeControler::direction dir);
		
		~EdgeControler();

		EdgeControler::direction getDirection();

	signals:
		void actMoved(EdgeControler::direction, QPoint);

		public slots:
		void onMousePress(Canvas*, QPoint);
		void onMouseMoved(Canvas*, QPoint);
		//void onParentResize(Canvas*, QSize);

	private:
		EdgeControler::direction mDirection;
		QPoint mousePressedGlobalCoor;
		
	};

	class Edges : public QObject
	{
		Q_OBJECT

	public:
		Edges(Canvas *parent);
		~Edges();
		
		public slots:
		//void onMousePress(Canvas*, QPoint);
		//void onMouseMoved(Canvas*, QPoint);
		void onControlerPressed();
		void onControlerMoved(EdgeControler::direction, QPoint);
		void onParentResize(Canvas*, QSize);

		Canvas* getParent();

	signals:
		void actResized(QSize size);

	private:
		Canvas* mParent;
		QMap<EdgeControler::direction, EdgeControler*> mEdges;
				
		int thickness, offset, corner, gap;
		
		QSize mousePressedParentSize;
	};
}

#endif // DUMMY_H