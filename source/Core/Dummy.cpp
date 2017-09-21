#include "Dummy.h"

namespace Jui
{

	// Header /////////////////////////////////////////////////////

	Header::Header(QWidget *parent) : Button(parent),
		m_parent(parent)
	{
		colorBackground_(QColor(60, 20, 20), QColor(120, 20, 20));
		thickness = 30;
		move(1, 1);
		fitSize();
		m_parent->installEventFilter(this);
	}
	void Header::fitSize() { setFixedSize(m_parent->size().width() - 2, thickness); }
	bool Header::eventFilter(QObject *object, QEvent *e) {
		switch (e->type())
		{
		case QEvent::Type::Resize:
			fitSize();
			return true;
		default:
			return false;
		};
	}
	void Header::mousePressEvent(QMouseEvent *e)
	{
		Button::mousePressEvent(e);
		mousePressedGlobalCoor = e->globalPos();

		if (this->parentWidget()->isWindow()) {
			mousePressedOriginCoor = this->parentWidget()->mapToGlobal(QPoint(0, 0));
		}
		else {
			mousePressedOriginCoor = this->parentWidget()->mapToParent(QPoint(0, 0));
		}
	}
	void Header::mouseMoveEvent(QMouseEvent *e)
	{
		QPoint deltaPt(
			e->globalPos().x() - mousePressedGlobalCoor.x(),
			e->globalPos().y() - mousePressedGlobalCoor.y()
		);
		QPoint newOrigin(
			mousePressedOriginCoor.x() + deltaPt.x(),
			mousePressedOriginCoor.y() + deltaPt.y()
		);
		this->parentWidget()->move(newOrigin);
	}
	void Header::paintEvent(QPaintEvent *event) {
		QPainter painter(this);
		painter.fillRect(rect(), colorBackground());
	}


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
	void EdgeControler::paintEvent(QPaintEvent *event) {

		Canvas::paintEvent(event);
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

	// EdgeControler2 /////////////////////////////////////////////////////

	EdgeControler2::EdgeControler2(QWidget *parent, Jui::direction dir) :
		Button(parent),
		m_direction(dir)
	{
		colorBackground_(QColor(20, 60, 20), QColor(120, 20, 20));
	}

	Jui::direction EdgeControler2::direction() { return m_direction; }

	void EdgeControler2::mousePressEvent(QMouseEvent *e)
	{
		Button::mousePressEvent(e);
		mousePressedGlobalCoor = e->globalPos();
	}
	void EdgeControler2::mouseMoveEvent(QMouseEvent *e)
	{
		QPoint deltaPt(
			e->globalPos().x() - mousePressedGlobalCoor.x(),
			e->globalPos().y() - mousePressedGlobalCoor.y()
		);
		emit actControlerMoved(m_direction, deltaPt);

		/*
				qDebug() << tr("EdgeControler onMouseMoved: deltaPt [%1, %2]").arg(
					QString::number(deltaPt.x()),
					QString::number(deltaPt.y())
				);
		*/

	}

	void EdgeControler2::paintEvent(QPaintEvent *event) {
		QPainter painter(this);
		painter.fillRect(rect(), colorBackground());
		painter.setPen(colorFrame());
		painter.drawLine(0, 0, width(), 0);
	}

	// Edges2 /////////////////////////////////////////////////////

	Edges2::Edges2(QWidget *parent) : QObject(parent),
		m_parent(parent)
	{
		thickness = 10;
		offset = 1;
		corner = 20;
		gap = 5;

		mEdges.insert(
			Jui::direction::right,
			new EdgeControler2(parent, Jui::direction::right)
		);
		mEdges.insert(
			Jui::direction::bottom,
			new EdgeControler2(parent, Jui::direction::bottom)
		);
		mEdges.insert(
			Jui::direction::left,
			new EdgeControler2(parent, Jui::direction::left)
		);
		mEdges.insert(
			Jui::direction::top,
			new EdgeControler2(parent, Jui::direction::top)
		);

		fitSize();
		m_parent->installEventFilter(this);

		foreach(EdgeControler2 *oneEdge, mEdges.values())
		{
			connect(
				oneEdge, SIGNAL(pressed()),
				this, SLOT(onControlerPressed())
			);
			connect(
				oneEdge, SIGNAL(actControlerMoved(Jui::direction, QPoint)),
				this, SLOT(onControlerMoved(Jui::direction, QPoint))
			);
		};
		/*

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
		*/
	}

	bool Edges2::eventFilter(QObject *object, QEvent *e) {
		switch (e->type())
		{
		case QEvent::Type::Resize:
			fitSize();
			break;
		};
		return false;
	}

	void Edges2::fitSize() {
		foreach(EdgeControler2* oneEdge, mEdges.values())
		{
			switch (oneEdge->direction())
			{
			case Jui::direction::right:
				oneEdge->setGeometry(
					m_parent->width() - thickness - offset,
					offset + corner + gap,
					thickness,
					m_parent->height() - 2 * offset - 2 * corner - 2 * gap
				);
				break;
			case Jui::direction::bottom:
				oneEdge->setGeometry(
					offset + corner + gap,
					m_parent->height() - offset - thickness,
					m_parent->width() - 2 * offset - 2 * corner - 2 * gap,
					thickness
				);
				break;
			case Jui::direction::left:
				oneEdge->setGeometry(
					offset,
					offset + corner + gap,
					thickness,
					m_parent->height() - 2 * offset - 2 * corner - 2 * gap
				);
				break;
			case Jui::direction::top:
				oneEdge->setGeometry(
					offset + corner + gap,
					offset,
					m_parent->width() - 2 * offset - 2 * corner - 2 * gap,
					thickness
				);
				break;
			}
		}
	}

	void Edges2::onControlerPressed() {
		if (m_parent->isWindow()) {
			mousePressedOriginCoor = m_parent->mapToGlobal(QPoint(0, 0));
		}
		else {
			mousePressedOriginCoor = m_parent->mapToParent(QPoint(0, 0));
		}
		mousePressedParentSize = m_parent->size();
	}
	void Edges2::onControlerMoved(Jui::direction dir, QPoint deltaPt) {
		QPoint origin(mousePressedOriginCoor);
		QSize size(mousePressedParentSize);

		switch (dir)
		{
		case Jui::direction::left:
			size.setWidth(mousePressedParentSize.width() - deltaPt.x());
			origin.setX(mousePressedOriginCoor.x() + deltaPt.x());
			m_parent->move(origin);
			//emit actEdgeMoved(origin);
			break;
		case Jui::direction::right:
			size.setWidth(mousePressedParentSize.width() + deltaPt.x());
			break;

		case Jui::direction::top:
			size.setHeight(mousePressedParentSize.height() - deltaPt.y());
			origin.setY(mousePressedOriginCoor.y() + deltaPt.y());
			m_parent->move(origin);
			//emit actEdgeMoved(origin);
			break;
		case Jui::direction::bottom:
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
		m_parent->setFixedSize(size);
		//emit actEdgeResized(size);
	}

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

