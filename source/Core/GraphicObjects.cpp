
#include "GraphicObjects.h"

namespace Jui
{
	// Scene /////////////////////////////////////////////////////

	Scene::Scene(QWidget *parent) : QGraphicsView(parent) {
		setWindowFlags(Qt::FramelessWindowHint);
		setFrameShape(QFrame::Shape::NoFrame);
		setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
		setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
		setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
		zoom = 1;
		zoomStep = 0.08;
		colorFrame.value_(50, 50, 50);
		colorBackground.value_(30, 30, 30);
		setScene(new QGraphicsScene(this));
		scene()->setSceneRect(-5000, -5000, 10000, 10000);
		show();
	}

	void Scene::geometry_(int x, int y, int w, int h) { setGeometry(x, y, w, h); }

	void Scene::mousePressEvent(QMouseEvent * event) {
		switch (event->buttons())
		{
		case Qt::RightButton:
		case Qt::MiddleButton:
			mouseAnchor = event->globalPos();
			sceneAnchor = mapToScene(QPoint(width() / 2, width() / 2));
			/*
			qDebug() << "Scene2::mousePressEvent RIGHT"
				<< "mouseAnchor" << mouseAnchor
				<< "sceneAnchor" << sceneAnchor
				;
			*/
			break;
		}
		QGraphicsView::mousePressEvent(event);
	}
	void Scene::mouseMoveEvent(QMouseEvent * event) {
		QGraphicsView::mouseMoveEvent(event);
		switch (event->buttons())
		{
		case Qt::RightButton:
		case Qt::MiddleButton:
			QPoint deltaPt(
				event->globalPos().x() - mouseAnchor.x(),
				event->globalPos().y() - mouseAnchor.y()
			);
			deltaPt.setX(deltaPt.x() / zoom);
			deltaPt.setY(deltaPt.y() / zoom);
			QPointF centerPt(
				sceneAnchor.x() - deltaPt.x(),
				sceneAnchor.y() - deltaPt.y()
			);
			/*
			qDebug() << "Scene2::mouseMoveEvent RIGHT"
				<< "deltaPt" << deltaPt
				<< "centerPt" << centerPt
				;
			*/
			centerOn(centerPt);
			break;
		}
		resetCachedContent();
	}
	void Scene::wheelEvent(QWheelEvent * event) {
		double scaleFactor = 1;
		QPointF centerPt = mapToScene(event->pos());

		if (event->angleDelta().y() > 0) {
			scaleFactor += zoomStep;
			zoom *= scaleFactor;
		}
		else {
			scaleFactor -= zoomStep;
			zoom *= scaleFactor;
		}
/*
		qDebug() << "Scene::wheelEvent"
			<< "angleDelta" << event->angleDelta()
			<< "pos" << event->pos()
			<< "zoom" << zoom
			;
*/
		scale(scaleFactor, scaleFactor);
		resetCachedContent();
	}

	void Scene::drawBackground(QPainter *painter, const QRectF & rect) {

		painter->fillRect(rect, colorBackground);
		painter->setPen(colorFrame);

		drawGrid(painter);

		QPen pen;
		pen.setWidth(2);

		pen.setColor(QColor(0, 255, 0));
		painter->setPen(pen);
		painter->drawLine(0, 0, 0, 10);

		pen.setColor(QColor(255, 0, 0));
		painter->setPen(pen);
		painter->drawLine(0, 0, 10, 0);

		QGraphicsView::drawBackground(painter, rect);
	}
	void Scene::drawGrid(QPainter *painter) {

		//int w = viewport()->width();
		//int h = viewport()->height();
		//int offset = 5;
		//QPolygonF sceneRect = mapToScene(QRect(0, 0, w, h));
		//QRectF bbox = sceneRect.boundingRect().adjusted(offset, offset, -offset, -offset);

		QRectF bbox = sceneRect();

		QPen penMainAxis(QColor(50, 50, 50), 1 / zoom);
		QPen penMinorAxis(QColor(40, 40, 40), 1 / zoom);

		for (int i = qFloor(bbox.left()); i < qCeil(bbox.right()); i++)
		{
			if (i % 10 == 0)
			{
				if (i % 100 == 0) { painter->setPen(penMainAxis); }
				else { painter->setPen(penMinorAxis); }
				painter->drawLine(i, bbox.top(), i, bbox.bottom());
			}
		}
		for (int i = qFloor(bbox.top()); i < qCeil(bbox.bottom()); i++)
		{
			if (i % 10 == 0)
			{
				if (i % 100 == 0) { painter->setPen(penMainAxis); }
				else { painter->setPen(penMinorAxis); }
				painter->drawLine(bbox.left(), i, bbox.right(), i);
			}
		}
	}

	// ScenePoint /////////////////////////////////////////////////////

	ScenePoint::ScenePoint(Scene *parent) : QGraphicsObject(0) {
		//qDebug() << "Point::addItem width:" << parent->width();
		parent->scene()->addItem(this);

		setAcceptHoverEvents(true);
		setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsMovable);

		thickness.value_(1);
		m_shape = ScenePoint::typeShape::CROSS;
		size_(8);
		colorPen.value_(150, 150, 150);

		//		QGraphicsScene *scene = static_cast<QGraphicsScene*>(parent);
		connect(
			&thickness, SIGNAL(changed()),
			this, SLOT(onChange())
		);
		connect(
			&colorPen, SIGNAL(changed()),
			this, SLOT(onChange())
		);
	}

	void ScenePoint::onChange() { this->update(boundingRect()); }

	void ScenePoint::origin_(double x, double y) { setPos(x, y); }
	void ScenePoint::size_(double s) { m_size = s; }
	void ScenePoint::typeShape_(ScenePoint::typeShape type) { m_shape = type; }

	QPointF ScenePoint::origin() { return pos(); }
	double ScenePoint::x() { return pos().x(); }
	double ScenePoint::y() { return pos().y(); }

	QRectF ScenePoint::boundingRect() const {
		/*
		return QRectF(
			-m_size / 2 - thickness,
			-m_size / 2 - thickness,
			m_size + 2 * thickness,
			m_size + 2 * thickness
		);
		*/
		return pointShape().controlPointRect().adjusted(
			-thickness, -thickness, thickness, thickness
		);
	}
	QPainterPath ScenePoint::pointShape() const {
		QPainterPath path;
		switch (m_shape)
		{
		case Jui::ScenePoint::typeShape::CIRCLE:
			path.addEllipse(QPointF(0, 0), m_size / 2, m_size / 2);
			break;
		case Jui::ScenePoint::typeShape::CROSS:
		default:
			path.moveTo(-m_size / 2, -m_size / 2);
			path.lineTo(m_size / 2, m_size / 2);
			path.moveTo(-m_size / 2, m_size / 2);
			path.lineTo(m_size / 2, -m_size / 2);
			break;
		}
		return path;
	}
	QPainterPath ScenePoint::shape() const {
		QPainterPathStroker stroke;
		stroke.setWidth(5);
		return stroke.createStroke(pointShape());
	}

	void ScenePoint::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
	{
		//qDebug() << "Point::hoverEnterEvent";
		thickness.value_(3, 0.2);
		QGraphicsObject::hoverEnterEvent(event);
	}
	void ScenePoint::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
	{
		//qDebug() << "Point::hoverLeaveEvent";
		thickness.value_(1, 1);
		QGraphicsObject::hoverLeaveEvent(event);
	}
	void ScenePoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
	{
		//qDebug() << "Point::mousePressEvent";
		colorPen.value_(250, 0, 0, 0.2);
		QGraphicsObject::mousePressEvent(event);
	}
	void ScenePoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
	{
		//qDebug() << "Point::mousePressEvent";
		colorPen.value_(150, 150, 150, 0.5);
		QGraphicsObject::mouseReleaseEvent(event);
	}
	void ScenePoint::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
	{
		//qDebug() << "Point::mouseMoveEvent";
		QGraphicsObject::mouseMoveEvent(event);
	}

	void ScenePoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
	{
		painter->setRenderHint(QPainter::Antialiasing);

		QPen pen;
		pen.setWidthF(thickness);
		pen.setColor(colorPen);
		painter->setPen(pen);
		painter->drawPath(pointShape());
		/*
		switch (m_shape)
		{
		case Jui::ScenePoint::typeShape::CROSS:
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
		case Jui::ScenePoint::typeShape::CIRCLE:
		default:
			painter->drawEllipse(boundingRect());
			break;
		}
		*/
		emit changed();
	}

	QDebug operator<<(QDebug dbg, ScenePoint &pt)
	{
		dbg.nospace() << "Point(" << pt.x() << ", " << pt.y() << ")";
		return dbg.space();
	}
	QDebug operator<<(QDebug dbg, ScenePoint *pt)
	{
		dbg.nospace() << *pt;
		return dbg.space();
	}

	// SceneLine /////////////////////////////////////////////////////

	SceneLine::SceneLine(Scene *parent, ScenePoint *from, ScenePoint *to) :
		QGraphicsObject(0),
		m_from(from),
		m_to(to)
	{
		parent->scene()->addItem(this);

		setAcceptHoverEvents(true);

		thickness.value_(1);
		colorPen.value_(150, 150, 150);

		connect(
			from, SIGNAL(changed()),
			this, SLOT(onChange())
		);
		connect(
			to, SIGNAL(changed()),
			this, SLOT(onChange())
		);
		connect(
			&thickness, SIGNAL(changed()),
			this, SLOT(onChange())
		);
		connect(
			&colorPen, SIGNAL(changed()),
			this, SLOT(onChange())
		);
	}

	QRectF SceneLine::boundingRect() const {
		double rectX, rectY, rectW, rectH;
		if (m_from->x() < m_to->x())
		{
			rectX = m_from->x();
			rectW = m_to->x() - m_from->x();
		}
		else
		{
			rectX = m_to->x();
			rectW = m_from->x() - m_to->x();
		}
		if (m_from->y() < m_to->y())
		{
			rectY = m_from->y();
			rectH = m_to->y() - m_from->y();
		}
		else
		{
			rectY = m_to->y();
			rectH = m_from->y() - m_to->y();
		}
		return QRect(rectX, rectY, rectW, rectH);
	}
	QPainterPath SceneLine::shape() const {
		QPainterPath path;
		path.moveTo(m_from->origin());
		path.lineTo(m_to->origin());
		return path;
	}

	void SceneLine::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
	{
		//qDebug() << "SceneLine::hoverEnterEvent";
		thickness.value_(3, 0.2);
		QGraphicsObject::hoverEnterEvent(event);
	}
	void SceneLine::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
	{
		//qDebug() << "SceneLine::hoverLeaveEvent";
		thickness.value_(1, 1);
		QGraphicsObject::hoverLeaveEvent(event);
	}

	void SceneLine::onChange() { this->update(boundingRect()); }
	void SceneLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
	{
		painter->setRenderHint(QPainter::Antialiasing);

		QPen pen;
		pen.setColor(colorPen);
		pen.setWidthF(thickness);
		painter->setPen(pen);
		painter->drawPath(shape());
	}
}