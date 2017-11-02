#include "Geometry.h"

namespace Jui
{
	// Point /////////////////////////////////////////////////////

	Point::Point(Canvas* parent) : AbstractGeometry(parent) {
		size = 8;
	};

	void Point::origin_(int x, int y) {
		originX = x;
		originY = y;

		bbox_(QRect(
			originX - size / 2, originY - size / 2,
			size, size
		));
	}

	void Point::draw(QPainter *painter) {
		painter->setPen(QColor(255, 0, 0));
		painter->drawLine(
			originX - size / 2, originY - size / 2,
			originX + size / 2, originY + size / 2
		);
		painter->drawLine(
			originX - size / 2, originY + size / 2,
			originX + size / 2, originY - size / 2
		);
	}

	// Line /////////////////////////////////////////////////////

	Line::Line(Canvas *parent) : AbstractGeometry(parent) {};

	void Line::from_(int x, int y) { fromPt = QPoint(x, y); }
	void Line::to_(int x, int y) { toPt = QPoint(x, y); }

	void Line::draw(QPainter *painter) {
		painter->setPen(QColor(255, 0, 0));
		painter->drawLine(fromPt, toPt);
	}
}