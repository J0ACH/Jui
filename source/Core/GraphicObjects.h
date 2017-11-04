#ifndef GRAPHICOBJECTS_H
#define GRAPHICOBJECTS_H

#include "Core.h"

namespace Jui
{

	// Scene /////////////////////////////////////////////////////

	class Scene : public QGraphicsView {

	public:
		Scene(QWidget *parent = Q_NULLPTR);

		void geometry_(int x, int y, int w, int h);

		QRectF sceneRect();

	protected:
		void drawBackground(QPainter * painter, const QRectF & rect) override;
		void mousePressEvent(QMouseEvent * event) override;
		void mouseMoveEvent(QMouseEvent * event) override;
		void wheelEvent(QWheelEvent * event) override;
		
		virtual void drawGrid(QPainter *painter);

	private:
		double zoom, zoomStep;
		FadeColor colorFrame, colorBackground;
		QPoint mouseAnchor;
		QPointF sceneAnchor;
		
	};

	// Point /////////////////////////////////////////////////////

	class ScenePoint : public QGraphicsObject
	{
		Q_OBJECT

	public:
		ScenePoint(Scene *parent);

		enum typeShape { CIRCLE, CROSS };

		void origin_(double x, double y);
		void size_(double s);
		void typeShape_(ScenePoint::typeShape type);

		QPointF origin();
		double x();
		double y();

		QRectF boundingRect() const;
		QPainterPath shape() const;
		void paint(
			QPainter *painter,
			const QStyleOptionGraphicsItem *option,
			QWidget *widget
		);

	signals:
		void changed();

	protected:
		virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
		virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
		virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
		virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
		virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

	private:
		typeShape m_shape;
		double m_size;

		FadeDouble thickness;
		FadeColor colorPen;

		QPainterPath pointShape() const;

		private slots:
		void onChange();
	};

	QDebug operator<<(QDebug dbg, ScenePoint *pt);
	QDebug operator<<(QDebug dbg, ScenePoint &pt);

	// SceneLine /////////////////////////////////////////////////////

	class SceneLine : public QGraphicsObject
	{
		Q_OBJECT

	public:
		SceneLine(Scene *parent, ScenePoint *from, ScenePoint *to);

		QRectF boundingRect() const;
		QPainterPath shape() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

	protected:
		virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
		virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

	private:
		ScenePoint *m_from, *m_to;

		FadeDouble thickness;
		FadeColor colorPen;

		private slots:
		void onChange();
	};
}

#endif // GRAPHICOBJECTS_H