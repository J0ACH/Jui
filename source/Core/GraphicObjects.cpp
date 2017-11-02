
#include "GraphicObjects.h"

namespace Jui
{
	// Scene /////////////////////////////////////////////////////

	Scene::Scene(QWidget *parent) : QGraphicsScene(parent),
		m_view(new QGraphicsView(this, parent))
	{
		m_view->setWindowFlags(Qt::FramelessWindowHint);
		m_view->setFrameShape(QFrame::Shape::NoFrame);
		//m_view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
		//m_view->setScene(this);
		m_view->setVerticalScrollBar(new ScrollBar(m_view));

		zoomDelta = 0.008;

		colorFrame.value_(50, 50, 50);
		colorBackground.value_(30, 30, 30);

		//setSceneRect(-w / 2, -h / 2, w, h);
		setSceneRect(-5000, -5000, 10000, 10000);
		//setSceneRect(-1, -1, 2, 2);

		m_view->show();
	}
	void Scene::geometry_(int x, int y, int w, int h)
	{
		m_view->setGeometry(x, y, w, h);
	}
	QRect Scene::itemBox(int margin)
	{

		//items() const
		return QRect();
	}
	QRectF Scene::viewBox()
	{
		int w = m_view->viewport()->width();
		int h = m_view->viewport()->height();
		QPolygonF sceneRect = m_view->mapToScene(QRect(0, 0, w, h));
		QRectF bbox = sceneRect.boundingRect();
		qDebug() << "Scene:viewBox"
			<< "width()" << w
			<< "height()" << h
			<< "bbox" << bbox
			;
		//return bbox.adjusted(-10,-10,-10,-10);
		return bbox;
	}
	void Scene::drawBackground(QPainter *painter, const QRectF & rect) {
		painter->fillRect(rect, colorBackground);
		painter->setPen(colorFrame);
		painter->drawLine(rect.left(), 0, rect.width(), 0);
		painter->drawLine(0, rect.top(), 0, rect.height());
		QGraphicsScene::drawBackground(painter, rect);
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

	void Scene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
		/*
		qDebug() << "Scene:mouseMoveEvent"
		<< "pos" << mouseEvent->pos()
		<< "scene" << mouseEvent->scenePos()
		<< "screen" << mouseEvent->screenPos()
		<< "view" << m_view->mapFromScene(mouseEvent->scenePos())
		;
		*/

		this->viewBox();

		mouseDelta = mouseEvent->screenPos();
		mouseAnchor = m_view->mapToScene(width() / 2, height() / 2); mouseEvent->scenePos();
		//qDebug() << "Scene:mapToScene" << m_view->mapToScene(mouseEvent->pos().x(), mouseEvent->pos().y());
		QGraphicsScene::mousePressEvent(mouseEvent);
	}
	void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
		switch (mouseEvent->buttons())
		{
		case Qt::RightButton:
			qDebug() << "Scene:mouseMoveEvent RIGHT" << mouseEvent->scenePos();
			//m_view->centerOn(mouseEvent->scenePos());
			break;
		case Qt::MiddleButton:
			//qDebug() << "Scene:mouseMoveEvent" << mouseEvent->scenePos();
	//	target_(mouseEvent->scenePos().x(), mouseEvent->scenePos().y());
			QPointF deltaPt;
			deltaPt.setX(mouseEvent->screenPos().x() - mouseDelta.x());
			deltaPt.setY(mouseEvent->screenPos().y() - mouseDelta.y());
			//qDebug() << "Scene:deltaPt" << deltaPt << sceneRect();
			QPointF centerPt;
			//centerPt.setX(mouseEvent->screenPos().x() + deltaPt.x());
			centerPt.setX(mouseAnchor.x() + deltaPt.x());
			centerPt.setY(mouseAnchor.y() + deltaPt.y());
			qDebug() << "Scene: deltaPt" << deltaPt << "centerPt" << centerPt << sceneRect();
			//m_view->centerOn(deltaPt);
			//m_view->translate(deltaPt.x(), deltaPt.y());
			m_view->centerOn(centerPt);
			//m_view->shear(deltaPt.x(), deltaPt.y());
			break;
		}
		QGraphicsScene::mouseMoveEvent(mouseEvent);
	}

	void Scene::wheelEvent(QGraphicsSceneWheelEvent *wheelEvent) {
		double scaleFactor = 1;
		if (wheelEvent->delta() > 0) { scaleFactor += zoomDelta; }
		else { scaleFactor -= zoomDelta; }
		//m_view->setTransformationAnchor(QGraphicsView::ViewportAnchor::AnchorViewCenter);
		//m_view->setTransformationAnchor(QGraphicsView::ViewportAnchor::AnchorUnderMouse);
		m_view->scale(scaleFactor, scaleFactor);
		//m_view->centerOn(wheelEvent->scenePos());

		//setSceneRect(viewBox());
		m_view->centerOn(wheelEvent->scenePos());

		/*
		qDebug() << "Scene:wheelEvent"
		<< "delta:" << wheelEvent->delta()
		<< "pos" << wheelEvent->pos()
		<< "scaleFactor:" << scaleFactor
		//"scenepos" << wheelEvent->scenePos() <<
		//"screenpos" << wheelEvent->screenPos() <<
		//"m_view->sceneRect()" << m_view->sceneRect()
		;
		*/

		//QGraphicsScene::wheelEvent(wheelEvent);
	}

	// ScrollBar /////////////////////////////////////////////////////

	ScrollBar::ScrollBar(QWidget *parent = 0) :QScrollBar(parent) { }
	void ScrollBar::wheelEvent(QWheelEvent * e) { 
		qDebug() << "ScrollBar::wheelEvent";
	}


	// ScenePoint /////////////////////////////////////////////////////

	ScenePoint::ScenePoint(Scene *parent) : QGraphicsObject(0) {
		//qDebug() << "Point::addItem width:" << parent->width();
		parent->addItem(this);

		setAcceptHoverEvents(true);
		setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsMovable);

		thickness.value_(1);
		m_shape = ScenePoint::typeShape::CROSS;
		size_(8);
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
		parent->addItem(this);

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