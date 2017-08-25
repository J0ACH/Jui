#include "Dummy.h"

namespace Jui
{
	// Header /////////////////////////////////////////////////////

	Header::Header(Canvas *parent) :
		Canvas(parent),
		thickness(35)
	{
		this->setBackgroundColor(120, 30, 30);
		this->setFrameAlpha(0);

		connect(
			this, SIGNAL(actMousePressed(Canvas*, QPoint)),
			this, SLOT(onMousePress(Canvas*, QPoint))
		);
		connect(
			this, SIGNAL(actMouseMoved(Canvas*, QPoint)),
			this, SLOT(onMouseMoved(Canvas*, QPoint))
		);
		connect(
			this, SIGNAL(actHeaderMoved(QPoint)),
			parent, SLOT(onMove(QPoint))
		);
		connect(
			parent, SIGNAL(actResized(Canvas*, QSize)),
			this, SLOT(onParentResize(Canvas*, QSize))
		);

		this->onParentResize(parent, parent->size());
	}

	void Header::onMousePress(Canvas* from, QPoint gpt)
	{
		mousePressedGlobalCoor = gpt;
		mousePressedOriginCoor = this->getParent()->getOrigin();
		this->getParent()->setFocus(Qt::MouseFocusReason);
		/*
		qDebug() << tr("Header2 onMousePress: parentOriginCoor [%1, %2]").arg(
			QString::number(mousePressedOriginCoor.x()),
			QString::number(mousePressedOriginCoor.y())
		);
		*/
	}
	void Header::onMouseMoved(Canvas* from, QPoint gpt)
	{
		QPoint deltaPt(
			gpt.x() - mousePressedGlobalCoor.x(),
			gpt.y() - mousePressedGlobalCoor.y()
		);
		QPoint newOrigin(
			mousePressedOriginCoor.x() + deltaPt.x(),
			mousePressedOriginCoor.y() + deltaPt.y()
		);
		emit actHeaderMoved(newOrigin);

		/*
		qDebug() << tr("Header2 onMouseMoved: deltaPt [%1, %2]").arg(
			QString::number(deltaPt.x()),
			QString::number(deltaPt.y())
		);
		*/
	}
	void Header::onParentResize(Canvas* from, QSize size)
	{
		this->move(1, 1);
		this->setFixedWidth(size.width() - 2);
		this->setFixedHeight(thickness);
	}

	Header::~Header() {	}

	// EdgeControler ///////////////////////////////////////////////////// 

	EdgeControler::EdgeControler(Canvas* parent, EdgeControler::direction dir) :
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
	}

	EdgeControler::direction EdgeControler::getDirection() { return mDirection; }

	void EdgeControler::onMousePress(Canvas* from, QPoint gpt)
	{
		mousePressedGlobalCoor = gpt;
		this->getParent()->setFocus(Qt::MouseFocusReason);
	}
	void EdgeControler::onMouseMoved(Canvas* from, QPoint gpt)
	{
		QPoint deltaPt(
			gpt.x() - mousePressedGlobalCoor.x(),
			gpt.y() - mousePressedGlobalCoor.y()
		);
		/*
		QPoint newOrigin(
			parentOriginCoor.x() + deltaPt.x(),
			parentOriginCoor.y() + deltaPt.y()
		);
		*/
		emit actControlerMoved(mDirection, deltaPt);

		qDebug() << tr("EdgeControler onMouseMoved: deltaPt [%1, %2]").arg(
			QString::number(deltaPt.x()),
			QString::number(deltaPt.y())
		);
	}
	EdgeControler::~EdgeControler() {}

	// Edges ///////////////////////////////////////////////////// 

	Edges::Edges(Canvas *parent) :
		QObject(parent),
		mParent(parent)
	{
		thickness = 10;
		offset = 5;
		corner = 30;
		gap = 5;

		mEdges.insert(
			EdgeControler::direction::Right,
			new EdgeControler(parent, EdgeControler::direction::Right)
		);
		mEdges.insert(
			EdgeControler::direction::Bottom,
			new EdgeControler(parent, EdgeControler::direction::Bottom)
		);
		mEdges.insert(
			EdgeControler::direction::Left,
			new EdgeControler(parent, EdgeControler::direction::Left)
		);
		mEdges.insert(
			EdgeControler::direction::Top,
			new EdgeControler(parent, EdgeControler::direction::Top)
		);

		this->onParentResize(parent, parent->size());

		foreach(EdgeControler *oneEdge, mEdges.values())
		{
			connect(
				oneEdge, SIGNAL(actMousePressed(Canvas*, QPoint)),
				this, SLOT(onControlerPressed())
			);
			connect(
				oneEdge, SIGNAL(actControlerMoved(EdgeControler::direction, QPoint)),
				this, SLOT(onControlerMoved(EdgeControler::direction, QPoint))
			);
		};

		connect(
			this, SIGNAL(actEdgeResized(QSize)),
			mParent, SLOT(setSize(QSize))
		);
		connect(
			this, SIGNAL(actEdgeMoved(QPoint)),
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
		mousePressedOriginCoor = mParent->getOrigin();
		mousePressedParentSize = mParent->size();
	}
	void Edges::onControlerMoved(EdgeControler::direction dir, QPoint deltaPt)
	{
		QPoint origin(mousePressedOriginCoor);
		QSize size(mousePressedParentSize);

		switch (dir)
		{
		case EdgeControler::direction::Left:
			size.setWidth(mousePressedParentSize.width() - deltaPt.x());
			origin.setX(mousePressedOriginCoor.x() + deltaPt.x());
			emit actEdgeMoved(origin);
			break;
		case EdgeControler::direction::Right:
			size.setWidth(mousePressedParentSize.width() + deltaPt.x());			
			break;

		case EdgeControler::direction::Top:
			size.setHeight(mousePressedParentSize.height() - deltaPt.y());
			origin.setY(mousePressedOriginCoor.y() + deltaPt.y());
			emit actEdgeMoved(origin);
			break;
		case EdgeControler::direction::Bottom:
			size.setHeight(mousePressedParentSize.height() + deltaPt.y());
			break;
		}

		/*
		qDebug() << tr("Edges onMouseMoved: deltaPt [%1, %2]").arg(
			QString::number(deltaPt.x()),
			QString::number(deltaPt.y())
		);
		*/
		/*
		qDebug() << tr("Edges onMouseMoved: size [%1, %2]").arg(
			QString::number(size.width()),
			QString::number(size.height())
		);
		*/

		emit actEdgeResized(size);
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

