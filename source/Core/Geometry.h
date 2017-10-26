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

	protected:
		void drawBackground(QPainter * painter, const QRectF & rect);

	};

	// Point /////////////////////////////////////////////////////

	class Point : public Canvas
	{
		Q_OBJECT

	public:
		Point(QWidget *parent = 0);

		enum shape { CIRCLE, CROSS };

		void x_(int x);
		void y_(int y);
		void size_(int s);

		int x();
		int y();

	protected:
		void paintEvent(QPaintEvent *e) override;

	private:
		shape m_shape;
	};

	QDebug operator<<(QDebug dbg, Point *pt);
	QDebug operator<<(QDebug dbg, Point &pt);

	// Line /////////////////////////////////////////////////////

	class Line : public Canvas
	{
		Q_OBJECT

	public:
		Line(QWidget *parent = 0);

		void from_(Point *pt);
		void to_(Point *pt);

	protected:
		void paintEvent(QPaintEvent *e) override;

	private:
		Point *m_from, *m_to;

		private slots:
		void fitCanvas();
	};
}

#endif // GEOMETRY_H