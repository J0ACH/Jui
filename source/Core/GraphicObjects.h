#ifndef GRAPHICOBJECTS_H
#define GRAPHICOBJECTS_H

#include "Core.h"

namespace Jui
{

	// Scene2 /////////////////////////////////////////////////////

	class Scene2 : public QGraphicsView {

	public:
		Scene2(QWidget *parent = Q_NULLPTR);

		void geometry_(int x, int y, int w, int h);

	protected:
		void drawBackground(QPainter * painter, const QRectF & rect) override;
		void mousePressEvent(QMouseEvent * event) override;
		void mouseMoveEvent(QMouseEvent * event) override;

		virtual void drawGrid(QPainter *painter);

	private:
		FadeColor colorFrame, colorBackground;
		QPoint mouseAnchor;
		QPointF sceneAnchor;

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

	// ScrollBar /////////////////////////////////////////////////////

	class ScrollBar : public QScrollBar {
	public:
		ScrollBar(QWidget *parent = 0);
	protected:
		virtual void wheelEvent(QWheelEvent * e) override;
	};

	// Point /////////////////////////////////////////////////////

	class ScenePoint : public QGraphicsObject
	{
		Q_OBJECT

	public:
		ScenePoint(Scene2 *parent);

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