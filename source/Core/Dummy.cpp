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

	// EdgeControler ///////////////////////////////////////////////////// 

	EdgeControler::EdgeControler(Canvas* parent, QObject* edges, EdgeControler::direction dir) :
		Canvas(parent),
		mDirection(dir)
	{
		this->setBackgroundColor(30, 200, 130);

		connect(
			this, SIGNAL(actMousePressed(Canvas*, QPoint)),
			this, SLOT(onMousePress(Canvas*, QPoint))
		);
		connect(
			this, SIGNAL(actMouseMoved(Canvas*, QPoint)),
			this, SLOT(onMouseMoved(Canvas*, QPoint))
		);

		connect(
			this, SIGNAL(actMousePressed(Canvas*, QPoint)),
			edges, SLOT(onControlerPressed())
		);
		connect(
			this, SIGNAL(actMoved(EdgeControler::direction, QPoint)),
			edges, SLOT(onControlerMoved(EdgeControler::direction, QPoint))
		);
			}

	EdgeControler::direction EdgeControler::getDirection() { return mDirection; }

	void EdgeControler::onMousePress(Canvas* from, QPoint gpt)
	{
		mousePressedGlobalCoor = gpt;
	}
	void EdgeControler::onMouseMoved(Canvas* from, QPoint gpt)
	{
		QPoint deltaPt(
			gpt.x() - mousePressedGlobalCoor.x(),
			gpt.y() - mousePressedGlobalCoor.y()
		);
		emit actMoved(mDirection, deltaPt);
	}
	EdgeControler::~EdgeControler() {}

	// Edges ///////////////////////////////////////////////////// 

	Edges::Edges(Canvas *parent) :
		QObject(parent),
		mParent(parent)
	{
		thickness = 20;
		offset = 5;
		corner = 30;
		gap = 5;

		mEdges.insert(
			EdgeControler::direction::Right,
			new EdgeControler(parent, this, EdgeControler::direction::Right)
		);
		mEdges.insert(
			EdgeControler::direction::Bottom,
			new EdgeControler(parent, this, EdgeControler::direction::Bottom)
		);
		mEdges.insert(
			EdgeControler::direction::Left,
			new EdgeControler(parent, this, EdgeControler::direction::Left)
		);
		mEdges.insert(
			EdgeControler::direction::Top,
			new EdgeControler(parent, this, EdgeControler::direction::Top)
		);

		this->onParentResize(parent, parent->size());

		connect(
			this, SIGNAL(actResized(QSize)),
			mParent, SLOT(setSize(QSize))
		);
		connect(
			this, SIGNAL(actMoved(QPoint)),
			mParent, SLOT(onMove(QPoint))
		);
		connect(
			mParent, SIGNAL(actResized(Canvas*, QSize)),
			this, SLOT(onParentResize(Canvas*, QSize))
		);
	}

	Canvas* Edges::getParent() { return mParent; }

	void Edges::onControlerPressed()
	{
		mousePressedParentSize = mParent->size();
		mousePressedGlobalCoor = mParent->getOrigin(true);
		//qDebug() << tr("Edges onControlerPressed");
	}
	void Edges::onControlerMoved(EdgeControler::direction dir, QPoint deltaPt)
	{
		QPoint origin(
			mousePressedGlobalCoor.x() + deltaPt.x(),
			mousePressedGlobalCoor.y() + deltaPt.y()
		);
		QSize size(
			mousePressedParentSize.width() + deltaPt.x(),
			mousePressedParentSize.height() + deltaPt.y()
		);

		switch (dir)
		{
		case EdgeControler::direction::Left:
			origin.setY(mousePressedGlobalCoor.y());
			size.setWidth(-deltaPt.x() + mousePressedParentSize.width());
			emit actMoved(origin);
		case EdgeControler::direction::Right:
			size.setHeight(mousePressedParentSize.height());
			break;

		case EdgeControler::direction::Top:
			origin.setX(mousePressedGlobalCoor.x());
			size.setHeight(-deltaPt.y() + mousePressedParentSize.height());
			emit actMoved(origin);
		case EdgeControler::direction::Bottom:
			size.setWidth(mousePressedParentSize.width());
			break;
		}	

		/*
		qDebug() << tr("Edges onMouseMoved: size [%1, %2]").arg(
			QString::number(size.width()),
			QString::number(size.height())
		);
		*/

		emit actResized(size);
	}

	void Edges::onParentResize(Canvas* from, QSize size)
	{
		foreach(EdgeControler* oneEdge, mEdges.values())
		{
			switch (oneEdge->getDirection())
			{
			case EdgeControler::direction::Right:
				oneEdge->setGeometry(
					from->width() - thickness - offset,
					offset + corner + gap,
					thickness,
					from->height() - 2 * offset - 2 * corner - 2 * gap
				);
				break;
			case EdgeControler::direction::Bottom:
				oneEdge->setGeometry(
					offset + corner + gap,
					from->height() - offset - thickness,
					from->width() - 2 * offset - 2 * corner - 2 * gap,
					thickness
				);
				break;
			case EdgeControler::direction::Left:
				oneEdge->setGeometry(
					offset,
					offset + corner + gap,
					thickness,
					from->height() - 2 * offset - 2 * corner - 2 * gap
				);
				break;
			case EdgeControler::direction::Top:
				oneEdge->setGeometry(
					offset + corner + gap,
					offset,
					from->width() - 2 * offset - 2 * corner - 2 * gap,
					thickness
				);
				break;
			}
		}
	}

	Edges::~Edges()
	{
	}
}

