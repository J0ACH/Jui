#include "Geometry.h"

namespace Jui
{

	// Point /////////////////////////////////////////////////////

	Point::Point(QWidget *parent) : Canvas(parent) {
		m_shape = Point::shape::CIRCLE;
		m_shape = Point::shape::CROSS;
		size_(10);
	}

	void Point::x_(int x) { originX_(x - size().width() / 2); }
	void Point::y_(int y) { originY_(y - size().height() / 2); }
	void Point::size_(int s) { setFixedSize(s, s); }

	void Point::paintEvent(QPaintEvent *e) {
		QPainter painter(this);
		QRect frameRect = QRect(0, 0, width() - 1, height() - 1);

		painter.setPen(QColor(255, 0, 0));

		switch (m_shape)
		{
		case Jui::Point::shape::CROSS:
			painter.drawLine(0, 0, width() - 1, height() - 1);
			painter.drawLine(0, height() - 1, width() - 1, 0);
			break;
		case Jui::Point::shape::CIRCLE:
		default:
			painter.drawEllipse(frameRect);
			break;
		}
	}

}