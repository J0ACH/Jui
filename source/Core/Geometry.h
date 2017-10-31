#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "Core.h"

namespace Jui
{

	// ScrollBar /////////////////////////////////////////////////////

	class ScrollBar : public QScrollBar {
	public:
		ScrollBar(QWidget * parent = 0);
	protected:
		void paintEvent(QPaintEvent *e) override;
	};

	// Scene /////////////////////////////////////////////////////

	class Scene : public QGraphicsScene {
		Q_OBJECT

	public:
		Scene(QWidget *parent = Q_NULLPTR);

		void geometry_(int x, int y, int w, int h);
		QRect itemBox(int margin = 50);
		QRectF viewBox();

	signals:
		void zoomed(double);

	protected:
		void drawBackground(QPainter * painter, const QRectF & rect);
		void drawForeground(QPainter * painter, const QRectF & rect);

		virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
		virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
		virtual void wheelEvent(QGraphicsSceneWheelEvent *wheelEvent) override;

	private:
		QGraphicsView *m_view;
		double zoomDelta;
		FadeColor colorFrame, colorBackground;
		QPointF mouseAnchor, mouseDelta;

		void drawGrid();

	};

	// Point /////////////////////////////////////////////////////

	class Point : public QGraphicsObject
	{
		Q_OBJECT

	public:
		Point(Scene *parent);

		enum shape { CIRCLE, CROSS };

		void origin_(double x, double y);
		void size_(double s);
		void shape_(Point::shape type);

		QRectF boundingRect() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

	protected:
		virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
		virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
		virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
		virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

	private:
		shape m_shape;
		double m_size;

		bool isOver;
		FadeDouble thickness;
		FadeColor colorPen;

		private slots:
		void onChange();
	};



	QDebug operator<<(QDebug dbg, Point *pt);
	QDebug operator<<(QDebug dbg, Point &pt);

	// Line /////////////////////////////////////////////////////

}

#endif // GEOMETRY_H