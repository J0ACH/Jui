#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "Core.h"

namespace Jui
{

	// Scene /////////////////////////////////////////////////////

	class Scene : public QGraphicsView
	{
	public:
		Scene(QWidget *parent = 0);
		
		void geometry_(int x, int y, int w, int h);
		void background_(QColor color);
		void background_(int r, int g, int b);

		QGraphicsScene scene();
		void addItem(QGraphicsItem *item);

	protected:
		void drawBackground(QPainter * painter, const QRectF & rect);
		void drawForeground(QPainter * painter, const QRectF & rect);

	private:
		QGraphicsScene *m_scene;
		FadeColor colorFrame, colorBackground;

	};

	// Point /////////////////////////////////////////////////////

	class Point : public QGraphicsItem
	{
		//Q_OBJECT

	public:
		Point(QGraphicsItem *parent = 0);
		
		enum shape { CIRCLE, CROSS };

		void origin_(double x, double y);
		//void x_(int x);
		//void y_(int y);
		void size_(double s);
		void shape_(Point::shape type);

		int x();
		int y();

		QRectF boundingRect() const;
		void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget) override;

	private:
		shape m_shape;
		double m_size;
	};

	QDebug operator<<(QDebug dbg, Point *pt);
	QDebug operator<<(QDebug dbg, Point &pt);

	// Line /////////////////////////////////////////////////////

}

#endif // GEOMETRY_H