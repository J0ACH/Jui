#include "Geometry.h"

namespace Jui
{
	// Scene /////////////////////////////////////////////////////

	Scene::Scene(QWidget *parent) : QGraphicsView(parent),
		m_scene(new QGraphicsScene(this))
	{
		//setCacheMode(QGraphicsView::CacheBackground);
		//setSceneRect(0, 0, 1000, 1000);
		setWindowFlags(Qt::FramelessWindowHint);
		setFrameShape(QFrame::Shape::NoFrame);
		setScene(m_scene);

		colorFrame.value_(250, 50, 50);
		colorBackground.value_(50, 50, 50);

		show();
	}

	QGraphicsScene Scene::scene() { return m_scene; }
	void Scene::addItem(QGraphicsItem *item) { m_scene->addItem(item); }

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

	Point::Point(QGraphicsItem *parent) : QGraphicsItem(parent) {
		m_shape = Point::shape::CROSS;
		size_(10);
	}

	void Point::origin_(double x, double y) { setPos(x, y); }
	//void Point::x_(int x) { originX_(x - m_size / 2); }
	//void Point::y_(int y) { originY_(y - size().height() / 2); }
	void Point::size_(double s) { m_size = s; }
	void Point::shape_(Point::shape type) { m_shape = type; }
	
	int Point::x() { return pos().x() + m_size / 2; }
	int Point::y() { return pos().y() + m_size / 2; }

	QRectF Point::boundingRect() const {
		qreal penWidth = 1;
		return QRectF(
			-m_size / 2 - penWidth / 2,
			-m_size / 2 - penWidth / 2,
			m_size + penWidth,
			m_size + penWidth
		);
	}

	void Point::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
		//void Point::paintEvent(QPaintEvent *e) {
	{
		QRect frameRect = QRect(0, 0, m_size - 1, m_size - 1);

		painter->setPen(QColor(255, 0, 0));

		switch (m_shape)
		{
		case Jui::Point::shape::CROSS:
			painter->drawLine(0, 0, m_size - 1, m_size - 1);
			painter->drawLine(0, m_size - 1, m_size - 1, 0);
			break;
		case Jui::Point::shape::CIRCLE:
		default:
			painter->drawEllipse(frameRect);
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


}