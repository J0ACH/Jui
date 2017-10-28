#include "Geometry.h"

namespace Jui
{
	// Scene /////////////////////////////////////////////////////

	Scene::Scene(QWidget *parent) : QGraphicsScene(parent),
		m_view(new QGraphicsView(this, parent))
	{
		m_view->setWindowFlags(Qt::FramelessWindowHint);
		m_view->setFrameShape(QFrame::Shape::NoFrame);
		//m_view->setScene(this);

		colorFrame.value_(50, 50, 50);
		colorBackground.value_(30, 30, 30);

		//setSceneRect(-w / 2, -h / 2, w, h);
		setSceneRect(-100, -100, 200, 200);
		m_view->show();
	}
	void Scene::geometry_(int x, int y, int w, int h)
	{
		m_view->setGeometry(x, y, w, h);
		
	}
	void Scene::drawBackground(QPainter *painter, const QRectF & rect) {
		painter->fillRect(rect, colorBackground);
		painter->setPen(colorFrame);
		painter->drawLine(rect.left(), 0, rect.width(), 0);
		painter->drawLine(0, rect.top(), 0, rect.height());

	}
	void Scene::drawForeground(QPainter *painter, const QRectF & rect) {
		//QRect rectFrame = QRect(
		//	this->
			//rect.left(), rect.top(), rect.width(), rect.height());
		//qDebug() << "Scene:drawForeground";// << rectFrame;
		//painter->setPen(colorFrame);
		//painter->drawRect(rectFrame);
		//painter->drawRect(rect.adjusted(0, 0, -1, -1));
	}

	void Scene::wheelEvent(QGraphicsSceneWheelEvent *wheelEvent) {
		qDebug() << "Scene:wheelEvent" <<
			"delta:" << wheelEvent->delta() <<
			"pos" << wheelEvent->pos() <<
			"scenepos" << wheelEvent->scenePos() <<
			"screenpos" << wheelEvent->screenPos() <<
			"m_view->sceneRect()" << m_view->sceneRect()
			;
		//m_view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
		if (wheelEvent->delta() > 0) { m_view->scale(1.1, 1.1); }
		else { m_view->scale(0.9, 0.9); }
		m_view->centerOn(wheelEvent->scenePos());
		//m_view->translate(1, 1);

	}

	// Point /////////////////////////////////////////////////////

	Point::Point(Scene *parent) : QGraphicsObject(0) {
		parent->addItem(this);

		isOver = false;
		thickness.value_(1.0);
		setAcceptHoverEvents(true);
		m_shape = Point::shape::CROSS;
		size_(10);
		colorPen.value_(150, 150, 150);

		QGraphicsScene *scene = static_cast<QGraphicsScene*>(parent);
		connect(
			&thickness, SIGNAL(changed()),
			this, SLOT(onChange())
		);
		connect(
			&colorPen, SIGNAL(changed()),
			this, SLOT(onChange())
		);
	}

	void Point::onChange() { this->update(boundingRect()); }

	void Point::origin_(double x, double y) { setPos(x, y); }
	void Point::size_(double s) { m_size = s; }
	void Point::shape_(Point::shape type) { m_shape = type; }

	QRectF Point::boundingRect() const {
		qreal penWidth = 1;
		return QRectF(
			-m_size / 2 - penWidth / 2,
			-m_size / 2 - penWidth / 2,
			m_size + penWidth,
			m_size + penWidth
		);
	}

	void Point::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
	{
		//qDebug() << "Point::hoverEnterEvent";
		thickness.value_(3, 0.2);
		isOver = true;
	}
	void Point::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
	{
		//qDebug() << "Point::hoverLeaveEvent";
		isOver = false;
		thickness.value_(1, 1);
	}
	void Point::mousePressEvent(QGraphicsSceneMouseEvent *event)
	{
		//qDebug() << "Point::mousePressEvent";
		colorPen.value_(250, 0, 0, 0.2);
	}
	void Point::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
	{
		//qDebug() << "Point::mousePressEvent";
		colorPen.value_(150, 150, 150, 0.5);
	}
	void Point::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
	{
		painter->setRenderHint(QPainter::Antialiasing);

		QPen pen;
		pen.setWidthF(thickness);
		pen.setColor(colorPen);
		painter->setPen(pen);

		switch (m_shape)
		{
		case Jui::Point::shape::CROSS:
			painter->drawLine(
				boundingRect().left(),
				boundingRect().top(),
				boundingRect().right(),
				boundingRect().bottom()
			);
			painter->drawLine(
				boundingRect().left(),
				boundingRect().bottom(),
				boundingRect().right(),
				boundingRect().top()
			);
			break;
		case Jui::Point::shape::CIRCLE:
		default:
			painter->drawEllipse(boundingRect());
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