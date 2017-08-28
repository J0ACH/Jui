#include "Dummy.h"

namespace Jui
{
	// Header /////////////////////////////////////////////////////

	Header::Header(Canvas *parent) :
		Canvas(parent),
		thickness(40)
	{
		this->setBackgroundColor(50, 30, 30);
		this->setFrameVisible(false);

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
			parent, SLOT(setOrigin(QPoint))
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
		this->setFixedWidth(size.width() - 1);
		this->setFixedHeight(thickness);
	}

	void Header::draw() {

		QPainter painter(this);

		switch (this->getState())
		{
		case Canvas::states::normal:
			painter.setPen(QColor(50, 50, 50));
			break;
		case Canvas::states::over:
			painter.setPen(QColor(250, 130, 130));
			break;
		case Canvas::states::active:
			painter.setPen(QColor(255, 255, 255));
			break;
		}
		painter.drawLine(0, height() - 2, width() - 1, height() - 2);
		painter.drawText(
			0, 0, this->width(), this->height(), Qt::AlignCenter, 
			this->getParent()->getName()
		);
	}

	Header::~Header() {	}

	// HeaderDialog /////////////////////////////////////////////////////

	HeaderDialog::HeaderDialog(Canvas *parent) :
		Header(parent),
		buttonClose(new Button(this))
	{
		this->setBackgroundColor(100, 30, 30);

		buttonClose->setName("X");
		buttonClose->setBackgroundVisible(false);
		buttonClose->setSize(QSize(30, 30));

		connect(
			buttonClose, SIGNAL(actPressed(Button*)),
			parent, SLOT(onClose())
		);
		connect(
			parent, SIGNAL(actResized(Canvas*, QSize)),
			this, SLOT(onParentResize(Canvas*, QSize))
		);

		this->onParentResize(parent, parent->size());
	}

	void HeaderDialog::onParentResize(Canvas* from, QSize size)
	{
		buttonClose->move(from->width() - 35, 5);
	}

	HeaderDialog::~HeaderDialog() {}

	// HeaderWindow /////////////////////////////////////////////////////

	HeaderWindow::HeaderWindow(Canvas *parent) :
		Header(parent),
		buttonClose(new Button(this)),
		buttonMaximize(new Button(this)),
		buttonMinimize(new Button(this))

	{
		this->setBackgroundColor(30, 30, 30);

		buttonClose->setName("X");
		buttonClose->setBackgroundVisible(false);
		buttonClose->setSize(QSize(30, 30));

		buttonMaximize->setName("[]");
		buttonMaximize->setBackgroundVisible(false);
		buttonMaximize->setSize(QSize(30, 30));

		buttonMinimize->setName("_");
		buttonMinimize->setBackgroundVisible(false);
		buttonMinimize->setSize(QSize(30, 30));

		connect(
			buttonClose, SIGNAL(actPressed(Button*)),
			parent, SLOT(onClose())
		);
		connect(
			parent, SIGNAL(actResized(Canvas*, QSize)),
			this, SLOT(onParentResize(Canvas*, QSize))
		);

		this->onParentResize(parent, parent->size());
	}

	void HeaderWindow::onParentResize(Canvas* from, QSize size)
	{
		buttonClose->move(from->width() - 35, 5);
		buttonMaximize->move(from->width() - 70, 5);
		buttonMinimize->move(from->width() - 105, 5);
	}

	HeaderWindow::~HeaderWindow() {}

	// EdgeControler ///////////////////////////////////////////////////// 

	EdgeControler::EdgeControler(Canvas* parent, EdgeControler::direction dir) :
		Canvas(parent),
		mDirection(dir)
	{
		this->setBackgroundVisible(false);
		this->setFrameVisible(false);

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
		emit actControlerMoved(mDirection, deltaPt);

		/*
		qDebug() << tr("EdgeControler onMouseMoved: deltaPt [%1, %2]").arg(
			QString::number(deltaPt.x()),
			QString::number(deltaPt.y())
		);
		*/
	}
	void EdgeControler::draw() {

		QPainter painter(this);

		switch (this->getState())
		{
		case Canvas::states::normal:
			painter.setPen(QColor(50, 50, 50));
			break;
		case Canvas::states::over:
			painter.setPen(QColor(250, 130, 130));
			break;
		case Canvas::states::active:
			painter.setPen(QColor(255, 255, 255));
			break;
		}

		switch (mDirection)
		{
		case EdgeControler::direction::Left:
			painter.drawLine(1, 0, 1, height());
			break;
		case EdgeControler::direction::Bottom:
			painter.drawLine(0, height() - 2, width() - 1, height() - 2);
			break;
		case EdgeControler::direction::Right:
			painter.drawLine(width() - 2, 0, width() - 2, height() - 1);
			break;
		case EdgeControler::direction::Top:
			painter.drawLine(0, 1, width(), 1);
			break;
		}
	}

	EdgeControler::~EdgeControler() {}

	// Edges ///////////////////////////////////////////////////// 

	Edges::Edges(Canvas *parent) :
		QObject(parent),
		mParent(parent)
	{
		thickness = 10;
		offset = 1;
		corner = 20;
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
			mParent, SLOT(setOrigin(QPoint))
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

