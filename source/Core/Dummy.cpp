#include "Dummy.h"

namespace Jui
{
	// Header /////////////////////////////////////////////////////

	Header::Header(Canvas *parent, int height) :
		Canvas(parent, 1, 1, parent->width() - 2, height)
	{
		this->setBackgroundColor(50, 30, 30);
		this->setFrameAlpha(0);

		connect(
			this, SIGNAL(actMoved(QPoint)),
			this->getParent(), SLOT(onMove(QPoint))
		);
	}

	void Header::mousePressEvent(QMouseEvent *event)
	{
		this->getParent()->setFocus(Qt::MouseFocusReason);

		mousePressedGlobalCoor = QPoint(event->globalPos().x(), event->globalPos().y());
		mousePressedLocalCoor = QPoint(event->x(), event->y());

		switch (this->getParent()->getType())
		{
		case Canvas::Window:
			mousePressedParentCoor = mousePressedGlobalCoor;
			break;
		case Canvas::Panel:
			mousePressedParentCoor = QPoint(
				event->x() + this->getParent()->getOrigin().x(),
				event->y() + this->getParent()->getOrigin().y()
			);
			break;
		}
	}
	void Header::mouseMoveEvent(QMouseEvent *event)
	{
		QPoint deltaPt(
			event->globalPos().x() - mousePressedGlobalCoor.x(),
			event->globalPos().y() - mousePressedGlobalCoor.y()
		);
		QPoint resultPt;

		switch (this->getParent()->getType())
		{
		case Canvas::Window:
			resultPt.setX(event->globalPos().x() - mousePressedLocalCoor.x());
			resultPt.setY(event->globalPos().y() - mousePressedLocalCoor.y());
			break;
		case Canvas::Panel:
			resultPt.setX(mousePressedParentCoor.x() + deltaPt.x() - mousePressedLocalCoor.x());
			resultPt.setY(mousePressedParentCoor.y() + deltaPt.y() - mousePressedLocalCoor.y());
			break;
		}
		emit actMoved(resultPt);
	}

	void Header::paintEvent(QPaintEvent *event)
	{
		Canvas::paintEvent(event);

		QPainter painter(this);

		painter.setPen(QColor(200, 30, 30));
		painter.drawText(0, 0, this->width(), this->height(), Qt::AlignCenter,
			this->getParent()->getName()
		);
		//painter.stroke();
	}

	Header::~Header()
	{
		//qDebug("Button closed");
	}

	// Edges ///////////////////////////////////////////////////// 

	Edge::Edge(Canvas *parent) : QObject(parent)
	{
		mParent = parent;

		thickness = 20;
		offset = 5;
		corner = 30;
		gap = 5;

		mEdges.insert(
			Edge::direction::Right,
			new Canvas(parent,
				parent->width() - thickness - offset,
				offset + corner + gap,
				thickness,
				parent->height() - 2 * offset - 2 * corner - 2 * gap
			)
		);

		mEdges.insert(
			Edge::direction::Bottom,
			new Canvas(parent,
				offset + corner + gap,
				parent->height() - offset - thickness,
				parent->width() - 2 * offset - 2 * corner - 2 * gap,
				thickness
			)
		);

		mEdges.insert(
			Edge::direction::Left,
			new Canvas(parent,
				offset,
				offset + corner + gap,
				thickness,
				parent->height() - 2 * offset - 2 * corner - 2 * gap
			)
		);

		mEdges.insert(
			Edge::direction::Top,
			new Canvas(parent,
				offset + corner + gap,
				offset,
				parent->width() - 2 * offset - 2 * corner - 2 * gap,
				thickness
			)
		);

		foreach(Canvas* oneEdge, mEdges.values())
		{
			oneEdge->setBackgroundColor(30, 200, 30);
			oneEdge->setFrameAlpha(0);

			connect(
				oneEdge, SIGNAL(actMousePressed(Canvas*, QPoint)),
				this, SLOT(onMousePress(Canvas*, QPoint))
			);
			connect(
				oneEdge, SIGNAL(actMouseMoved(Canvas*, QPoint)),
				this, SLOT(onMouseMoved(Canvas*, QPoint))
			);
			connect(
				this, SIGNAL(actResized(QSize)),
				mParent, SLOT(onResize(QSize))
			);
		};
	}

	void Edge::setDirection(Edge::direction dir, bool visibilty)
	{

	}

	void Edge::onMousePress(Canvas* from, QPoint gpt)
	{
		/*
		qDebug() << tr("Edge onPress: pt [%1, %2]").arg(
			QString::number(gpt.x()),
			QString::number(gpt.y())
		);
		*/

		mousePressedGlobalCoor = gpt;
		mousePressedLocalCoor = from->mapFromGlobal(gpt);
		mousePressedParentCoor = from->getOrigin();
		mousePressedParentSize = mParent->size();

		/*
		qDebug() << tr("Edge onPress: parentOrigin [%1, %2]").arg(
			QString::number(mousePressedParentCoor.x()),
			QString::number(mousePressedParentCoor.y())
		);
		*/
	}
	void Edge::onMouseMoved(Canvas* from, QPoint gpt)
	{
		QPoint deltaPt(
			gpt.x() - mousePressedGlobalCoor.x(),
			gpt.y() - mousePressedGlobalCoor.y()
		);
		QSize size(
			mousePressedParentSize.width() + deltaPt.x(),
			mousePressedParentSize.height() + deltaPt.y()
		);

		qDebug() << tr("Edge onMouseMoved: size [%1, %2]").arg(
			QString::number(size.width()),
			QString::number(size.height())
		);

		emit actResized(size);
	}
	/*

		Edge::fitPosition()
		{

		}
	*/

	Edge::~Edge()
	{
	}
}

