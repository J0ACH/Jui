#include "Geometry.h"

namespace Jui
{
	// Scene /////////////////////////////////////////////////////

	Scene::Scene(QWidget *parent) : QGraphicsView(parent),
		scene(new QGraphicsScene(this))
	{
		//setCacheMode(QGraphicsView::CacheBackground);
		//setSceneRect(0, 0, 1000, 1000);
		setWindowFlags(Qt::FramelessWindowHint);
		setFrameShape(QFrame::Shape::NoFrame);
		setScene(scene);

		colorFrame.value_(250, 50, 50);
		colorBackground.value_(50, 50, 50);

		show();
	}
	void Scene::geometry_(int x, int y, int w, int h)
	{
		this->setGeometry(x, y, w, h);
	}

	void Scene::background_(QColor color) { colorBackground.value_(color); }
	void Scene::background_(int r, int g, int b) { Scene::background_(QColor(r, g, b)); }
	void Scene::drawBackground(QPainter *painter, const QRectF & rect) {
		painter->fillRect(rect, colorBackground);
	}
	void Scene::drawForeground(QPainter *painter, const QRectF & rect) {
		painter->setPen(colorFrame);
		painter->drawRect(rect.adjusted(0, 0, -1, -1));
	}


	// Point /////////////////////////////////////////////////////

	Point::Point(QWidget *parent) : Canvas(parent) {
		m_shape = Point::shape::CROSS;
		size_(10);
	}

	void Point::x_(int x) { originX_(x - size().width() / 2); }
	void Point::y_(int y) { originY_(y - size().height() / 2); }
	void Point::size_(int s) { setFixedSize(s, s); }

	int Point::x() { return origin().x() + size().width() / 2; }
	int Point::y() { return origin().y() + size().height() / 2; }

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

	QDebug operator<<(QDebug dbg, Point &pt)
	{
		dbg.nospace() << "Point(" << pt.x() << ", " << pt.y() << ")";
		return dbg.space();
	}
	QDebug operator<<(QDebug dbg, Point *pt)
	{
		dbg.nospace() << *pt;
		return dbg.space();
	}

	// Line /////////////////////////////////////////////////////

	Line::Line(QWidget *parent) : Canvas(parent),
		m_from(nullptr),
		m_to(nullptr)
	{

	}

	void Line::from_(Point *pt) {
		m_from = pt;
		fitCanvas();
	}
	void Line::to_(Point *pt) {
		m_to = pt;
		fitCanvas();
	}

	void Line::fitCanvas() {
		if (m_from != nullptr && m_to != nullptr)
		{
			if (m_from->x() < m_to->x()) { originX_(m_from->x()); }
			else { originX_(m_to->x()); }
			if (m_from->y() < m_to->y()) { originY_(m_from->y()); }
			else { originY_(m_to->y()); }

			int w = m_to->x() - m_from->x();
			int h = m_to->y() - m_from->y();

			if (w < 0) { w *= -1; }
			if (h < 0) { h *= -1; }

			setFixedSize(w, h);

			qDebug() << "from" << m_from << "to" << m_to;
			qDebug() << "w:" << w << "h:" << h;
		}
	}

	void Line::paintEvent(QPaintEvent *e) {
		QPainter painter(this);
		QRect frameRect = QRect(0, 0, width() - 1, height() - 1);

		painter.setPen(QColor(255, 0, 0));
		painter.drawLine(0, 0, width() - 1, height() - 1);

	}

}