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

	/*
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
	*/

	
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
		/*
		qDebug() << tr("EdgeControler onMousePress: pt [%1, %2]").arg(
			QString::number(mousePressedGlobalCoor.x()),
			QString::number(mousePressedGlobalCoor.y())
		);
		*/
	}
	void EdgeControler::onMouseMoved(Canvas* from, QPoint gpt)
	{
		QPoint deltaPt(
			gpt.x() - mousePressedGlobalCoor.x(),
			gpt.y() - mousePressedGlobalCoor.y()
		);
		emit actMoved(mDirection, deltaPt);
		/*
		qDebug() << tr("EdgeControler onMouseMoved: deltaPt [%1, %2]").arg(
			QString::number(deltaPt.x()),
			QString::number(deltaPt.y())
		);
		*/
		
	}
	/*
	void EdgeControler::onParentResize(Canvas* from, QSize size)
	{
		switch (mDirection)
		{
		case EdgeControler::direction::Right:
			this->setGeometry(
				from->width() - thickness - offset,
				offset + corner + gap,
				thickness,
				from->height() - 2 * offset - 2 * corner - 2 * gap
			);
			break;
		case EdgeControler::direction::Bottom:
			this->setGeometry(
				offset + corner + gap,
				from->height() - offset - thickness,
				from->width() - 2 * offset - 2 * corner - 2 * gap,
				thickness
			);
			break;
		case EdgeControler::direction::Left:
			this->setGeometry(
				offset,
				offset + corner + gap,
				thickness,
				from->height() - 2 * offset - 2 * corner - 2 * gap
			);
			break;
		case EdgeControler::direction::Top:
			this->setGeometry(
				offset + corner + gap,
				offset,
				from->width() - 2 * offset - 2 * corner - 2 * gap,
				thickness
			);
			break;
		}
	}
	*/

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

		/*
		mEdges.insert(
			EdgeControler::direction::Bottom,
			new EdgeControler(parent, this, EdgeControler::direction::Bottom)
		);

		mEdges.insert(
			EdgeControler::direction::Right,
			new EdgeControler(parent, EdgeControler::direction::Right)
		);
		mEdges.insert(
			EdgeControler::direction::Bottom,
			new EdgeControler(parent, EdgeControler::direction::Bottom)
		);
		*/

		/*
				//mEdges.insert(Edges::direction::Right, new Canvas(parent));
				mEdges.insert(Edges::direction::Bottom, new Canvas(parent));
				mEdges.insert(Edges::direction::Left, new Canvas(parent));
				mEdges.insert(Edges::direction::Top, new Canvas(parent));
		*/

		this->onParentResize(parent, parent->size());

		connect(
			this, SIGNAL(actResized(QSize)),
			mParent, SLOT(setSize(QSize))
		);
		connect(
			mParent, SIGNAL(actResized(Canvas*, QSize)),
			this, SLOT(onParentResize(Canvas*, QSize))
		);

		/*
		foreach(Canvas* oneEdge, mEdges.values())
		{
			oneEdge->setBackgroundColor(30, 200, 30);
			oneEdge->setFrameAlpha(0);
			oneEdge->setName(
				tr("CanvasEdge_%1").arg(
					QString::number(mEdges.key(oneEdge))
				)
			);

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
				mParent, SLOT(setSize(QSize))
			);
			connect(
				mParent, SIGNAL(actResized(Canvas*, QSize)),
				this, SLOT(onParentResize(Canvas*, QSize))
			);
		};
		*/
	}

	/*
	void Edges::setDirection(Edges::direction dir, bool visibilty)
	{

	}
	*/

	/*
		Edges::direction Edges::getDirection(Canvas* from)
		{
			if (from->getName() == "CanvasEdge_0")
			{
				qDebug() << tr("Edge name right");
				return Edges::direction::Right;
			}
			else if (from->getName() == "CanvasEdge_1")
			{
				qDebug() << tr("Edge name bottom");
				return Edges::direction::Bottom;
			}
			else
			{
				qDebug() << tr("Edge name [%1]").arg(from->getName());
				return Edges::direction::Right;
			}
		}

		void Edges::onMousePress(Canvas* from, QPoint gpt)
		{

			mousePressedGlobalCoor = gpt;
			mousePressedLocalCoor = from->mapFromGlobal(gpt);
			mousePressedParentCoor = from->getOrigin();
			mousePressedParentSize = mParent->size();

			this->getDirection(from);

		}
		void Edges::onMouseMoved(Canvas* from, QPoint gpt)
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
	*/

	Canvas* Edges::getParent() { return mParent; }

	void Edges::onControlerPressed()
	{
		mousePressedParentSize = mParent->size();
		//qDebug() << tr("Edges onControlerPressed");
	}
	void Edges::onControlerMoved(EdgeControler::direction dir, QPoint deltaPt)
	{
		QSize size(
			mousePressedParentSize.width() + deltaPt.x(),
			mousePressedParentSize.height() + deltaPt.y()
		);
		/*
		switch (oneDir)
		{
		case Edge::direction::Right:
		break;
		}
		*/

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
		/*
				foreach(Edges::direction oneDir, mEdges.keys())
				{
					Canvas *edge = mEdges.value(oneDir);
					switch (oneDir)
					{
					case Edges::direction::Right:
						edge->setGeometry(
							from->width() - thickness - offset,
							offset + corner + gap,
							thickness,
							from->height() - 2 * offset - 2 * corner - 2 * gap
						);
						break;
					case Edges::direction::Bottom:
						edge->setGeometry(
							offset + corner + gap,
							from->height() - offset - thickness,
							from->width() - 2 * offset - 2 * corner - 2 * gap,
							thickness
						);
						break;
					case Edges::direction::Left:
						edge->setGeometry(
							offset,
							offset + corner + gap,
							thickness,
							from->height() - 2 * offset - 2 * corner - 2 * gap
						);
						break;
					case Edges::direction::Top:
						edge->setGeometry(
							offset + corner + gap,
							offset,
							from->width() - 2 * offset - 2 * corner - 2 * gap,
							thickness
						);
						break;
					}
				}

		*/
	}


	Edges::~Edges()
	{
	}
}

