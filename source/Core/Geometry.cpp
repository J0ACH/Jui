#include "Geometry.h"

namespace Jui
{

	// ScrollBar /////////////////////////////////////////////////////

	ScrollBar::ScrollBar(QWidget *parent) { }
	void ScrollBar::paintEvent(QPaintEvent *e) {
		QScrollBar::paintEvent(e);
		//QPainter painter;
		//painter.fillRect(rect(), QColor(255, 0, 0));
	}

	// Scene /////////////////////////////////////////////////////

	Scene::Scene(QWidget *parent) : QGraphicsScene(parent),
		m_view(new QGraphicsView(this, parent))
	{
		m_view->setWindowFlags(Qt::FramelessWindowHint);
		m_view->setFrameShape(QFrame::Shape::NoFrame);
		//m_view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
		//m_view->setScene(this);
		//m_view->setVerticalScrollBar(new ScrollBar(m_view));

		zoomDelta = 0.008;

		colorFrame.value_(50, 50, 50);
		colorBackground.value_(30, 30, 30);

		//setSceneRect(-w / 2, -h / 2, w, h);
		//setSceneRect(-5000, -5000, 10000, 10000);
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

		if (mouseEvent->buttons() == Qt::MiddleButton)
		{
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

	// Point /////////////////////////////////////////////////////

	Point::Point(Scene *parent) : QGraphicsObject(0) {
		//qDebug() << "Point::addItem width:" << parent->width();
		parent->addItem(this);

		setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsMovable);

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
		QGraphicsObject::hoverEnterEvent(event);
	}
	void Point::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
	{
		//qDebug() << "Point::hoverLeaveEvent";
		isOver = false;
		thickness.value_(1, 1);
		QGraphicsObject::hoverLeaveEvent(event);
	}
	void Point::mousePressEvent(QGraphicsSceneMouseEvent *event)
	{
		//qDebug() << "Point::mousePressEvent";
		colorPen.value_(250, 0, 0, 0.2);
		QGraphicsObject::mousePressEvent(event);
	}
	void Point::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
	{
		//qDebug() << "Point::mousePressEvent";
		colorPen.value_(150, 150, 150, 0.5);
		QGraphicsObject::mouseReleaseEvent(event);
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

	Line::Line(Canvas* parent) : AbstractGeometry(parent) {};

	void Line::from_(int x, int y) { fromPt = QPoint(x, y); }
	void Line::to_(int x, int y) { toPt = QPoint(x, y); }

	void Line::draw(QPainter *painter) {
		painter->setPen(QColor(255, 0, 0));
		painter->drawLine(fromPt, toPt);
	}
}