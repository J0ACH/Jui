#include "Dummy.h"

namespace Jui
{

	Header::Header(Canvas *parent, int height) :
		Canvas(parent, 1, 1, parent->width() - 2, height)
	{
		this->setBackgroundColor(50, 30, 30);
		this->setFrameAlpha(0);

		connect(
			this, SIGNAL(actMoved(QPoint)),
			this->parentWidget(), SLOT(onMove(QPoint))
		);
	}

	void Header::mousePressEvent(QMouseEvent *event)
	{
		this->parent()->setFocus(Qt::MouseFocusReason);

		mousePressedGlobalCoor = QPoint( event->globalPos().x(), event->globalPos().y());
		mousePressedLocalCoor = QPoint(event->x(), event->y());
		switch (this->parent()->getType())
		{
		case Canvas::Window:
			mousePressedParentCoor = mousePressedGlobalCoor;
			break;
		case Canvas::Panel:
			mousePressedParentCoor = QPoint(
				event->x() + this->parent()->getOrigin().x(),
				event->y() + this->parent()->getOrigin().y()
			);
			break;
		}

		qDebug() << tr("Header mousePressEvent: "
			"\n\t mousePressedGlobalCoor [%1, %2]"
			"\n\t mousePressedLocalCoor [%3, %4]"
			"\n\t mousePressedParentCoor [%5, %6]"		
		).arg(
			QString::number(mousePressedGlobalCoor.x()),
			QString::number(mousePressedGlobalCoor.y()),
			QString::number(mousePressedLocalCoor.x()),
			QString::number(mousePressedLocalCoor.y()),
			QString::number(mousePressedParentCoor.x()),
			QString::number(mousePressedParentCoor.y())
		);
			
	}
	void Header::mouseMoveEvent(QMouseEvent *event)
	{
		QPoint deltaPt(
			event->globalPos().x() - mousePressedGlobalCoor.x(),
			event->globalPos().y() - mousePressedGlobalCoor.y()
		);
		QPoint resultPt;

		switch (this->parent()->getType())
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
		
		qDebug() << tr("Header mouseMoveEvent: pt [%1, %2]").arg(
			QString::number(resultPt.x()),
			QString::number(resultPt.y())
		);

		emit actMoved(resultPt);
	}

	void Header::paintEvent(QPaintEvent *event)
	{
		Canvas::paintEvent(event);

		QPainter painter(this);

		painter.setPen(QColor(200, 30, 30));
		painter.drawText(0, 0, this->width(), this->height(), Qt::AlignCenter,
			this->parent()->getName()
		);
		//painter.stroke();
	}


	Header::~Header()
	{
		//qDebug("Button closed");
	}

}

