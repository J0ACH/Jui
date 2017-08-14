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

		mousePressedGlobalCoor = QPoint( event->globalPos().x(), event->globalPos().y());
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

	Edge::Edge(Canvas *parent, int height)
	{
		test = new Canvas(parent, 1, 1, height, parent->height());
		test->setBackgroundColor(30, 230, 30);
		test->setFrameAlpha(0);
	}

	Edge::~Edge()
	{
	}
}

