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
		temp = QPoint(event->globalPos().x(), event->globalPos().y());
		temp2 = this->getParent()->geometry();
	}
	void Header::mouseMoveEvent(QMouseEvent *event)
	{
		Canvas *parent = this->getParent();
		QPoint globalPt(event->globalPos().x(), event->globalPos().y());
		QPoint localPt(event->x(), event->y());
		QPoint resultPt;

		if (parent->isWin())
		{
			resultPt.setX(globalPt.x() - lastPressedMousePosition.x());
			resultPt.setY(globalPt.y() - lastPressedMousePosition.y());
		}
		else
		{
			QPoint difPt(
				globalPt.x() - temp.x(),
				globalPt.y() - temp.y()
			);

			QPoint resultPt(
				temp2.topLeft().x() + lastPressedMousePosition.x() + difPt.x(),
				temp2.topLeft().y() + lastPressedMousePosition.y() + difPt.y()
			);
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
			this->getParent()->getName()
		);
		//painter.stroke();
	}


	Header::~Header()
	{
		//qDebug("Button closed");
	}

}

