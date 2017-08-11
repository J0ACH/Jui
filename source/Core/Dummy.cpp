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
		this->parentWidget()->setFocus(Qt::MouseFocusReason);
		lastPressedMousePosition = QPoint(event->x(), event->y());
	}
	void Header::mouseMoveEvent(QMouseEvent *event)
	{
		QPoint globalPt(event->globalPos().x(), event->globalPos().y());
		QPoint resultPt(
			globalPt.x() - lastPressedMousePosition.x(),
			globalPt.y() - lastPressedMousePosition.y()
		);
		/*
		qDebug() << tr("Header mouseMoveEvent: pt [%1, %2]").arg(
			QString::number(resultPt.x()),
			QString::number(resultPt.y())
		);
		 */
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

}

