#include "Dummies.h"

namespace Jui
{
	// Header /////////////////////////////////////////////////////

	Header::Header(QWidget *parent) : QWidget(parent),
		//m_text(new PureText(this)),
		title(new QLabel(this))
	{
		title->setFont(QFont("Segoe UI Light", 9));
		title->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

		thickness = 30;
		move(1, 1);
		isLocked = false;

		background_(40, 40, 40);

		currentColorBackground.value_(colorBackground);
		connect(
			&currentColorBackground, SIGNAL(changed()),
			this, SLOT(update())
		);

		connect(
			parent, SIGNAL(resized(QSize)),
			this, SLOT(onParentResize(QSize))
		);

		onParentResize(parent->size());
		show();
	}
	void Header::name_(QString name) { setWindowTitle(name); }
	void Header::font_(QString family) { title->setFont(family); }
	void Header::lock_(bool b) { isLocked = b; }
	void Header::height_(int y) {
		thickness = y;
		onParentResize(size());
	}
	void Header::background_(int r, int g, int b) {
		colorBackground = QColor(r, g, b);
		currentColorBackground.value_(colorBackground);
	}

	void Header::onParentResize(QSize size) {
		setFixedSize(size.width() - 2, thickness - 1);
		title->setGeometry(20, 0, size.width() - 2, thickness - 1);
	}
	void Header::mousePressEvent(QMouseEvent *e)
	{
		parentWidget()->setFocus();

		if (!isLocked) {
			mousePressedGlobalCoor = e->globalPos();

			if (this->parentWidget()->isWindow()) {
				mousePressedOriginCoor = this->parentWidget()->mapToGlobal(QPoint(0, 0));
			}
			else {
				mousePressedOriginCoor = this->parentWidget()->mapToParent(QPoint(0, 0));
			}
			currentColorBackground.value_(90, 90, 90, 0.05);
		}
	}
	void Header::mouseReleaseEvent(QMouseEvent *e) {
		if (!isLocked) {
			currentColorBackground.value_(colorBackground, 0.5);
		}
	}
	void Header::mouseMoveEvent(QMouseEvent *e)
	{
		if (!isLocked) {
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
	}
	void Header::paintEvent(QPaintEvent *event) {
		QPainter painter(this);
		if (!isLocked) { painter.fillRect(rect(), currentColorBackground); }
		//m_text->text_(windowTitle());
		title->setText(windowTitle());
	}

	// EdgeControler /////////////////////////////////////////////////////

	EdgeControler::EdgeControler(QWidget *parent, Jui::direction dir) :
		QWidget(parent),
		m_direction(dir)
	{
		colorFrame.value_(QColor(0, 0, 0, 0));
		connect(
			&colorFrame, SIGNAL(changed()),
			this, SLOT(update())
		);
		show();
	}
	Jui::direction EdgeControler::direction() { return m_direction; }
	void EdgeControler::enterEvent(QEvent *e) {
		colorFrame.value_(QColor(100, 100, 100), 0.2);
		switch (m_direction)
		{
		case Jui::direction::right:
		case Jui::direction::left:
			setCursor(QCursor(Qt::SizeHorCursor));
			break;

		case Jui::direction::top:
		case Jui::direction::bottom:
			setCursor(QCursor(Qt::SizeVerCursor));
			break;
		}
	}
	void EdgeControler::leaveEvent(QEvent *e) {
		colorFrame.value_(QColor(0, 0, 0, 0), 1);
		setCursor(QCursor(Qt::ArrowCursor));
	}
	void EdgeControler::mousePressEvent(QMouseEvent *e)
	{
		parentWidget()->setFocus();
		colorFrame.value_(QColor(200, 200, 200), 0.05);
		mousePressedGlobalCoor = e->globalPos();
		emit pressed();
	}
	void EdgeControler::mouseReleaseEvent(QMouseEvent *e)
	{
		colorFrame.value_(QColor(100, 100, 100), 1);
	}
	void EdgeControler::mouseMoveEvent(QMouseEvent *e)
	{
		QPoint deltaPt(
			e->globalPos().x() - mousePressedGlobalCoor.x(),
			e->globalPos().y() - mousePressedGlobalCoor.y()
		);
		emit controlerMoved(m_direction, deltaPt);
	}
	void EdgeControler::paintEvent(QPaintEvent *event)
	{
		QPainter painter(this);
		painter.setPen(colorFrame);
		switch (m_direction)
		{
		case Jui::direction::right:
			painter.drawLine(width() - 2, 0, width() - 2, height());
			break;
		case Jui::direction::bottom:
			painter.drawLine(0, height() - 2, width(), height() - 2);
			break;
		case Jui::direction::left:
			painter.drawLine(1, 0, 1, height());
			break;
		case Jui::direction::top:
			painter.drawLine(0, 1, width(), 1);
			break;
		default:
			painter.drawLine(0, 0, width(), height());
			break;
		}
	}

	// Edges /////////////////////////////////////////////////////

	Edges::Edges(QWidget *parent) : QObject(parent),
		m_parent(parent)
	{
		thickness = 12;
		offset = 2;
		corner = 20;
		gap = 5;

		mEdges.insert(
			Jui::direction::right,
			new EdgeControler(parent, Jui::direction::right)
		);
		mEdges.insert(
			Jui::direction::bottom,
			new EdgeControler(parent, Jui::direction::bottom)
		);
		mEdges.insert(
			Jui::direction::left,
			new EdgeControler(parent, Jui::direction::left)
		);
		mEdges.insert(
			Jui::direction::top,
			new EdgeControler(parent, Jui::direction::top)
		);

		connect(
			parent, SIGNAL(resized(QSize)),
			this, SLOT(onParentResize(QSize))
		);
		onParentResize(parent->size());

		foreach(EdgeControler *oneEdge, mEdges.values())
		{
			connect(
				oneEdge, SIGNAL(pressed()),
				this, SLOT(onControlerPressed())
			);
			connect(
				oneEdge, SIGNAL(controlerMoved(Jui::direction, QPoint)),
				this, SLOT(onControlerMoved(Jui::direction, QPoint))
			);
		};
	}
	void Edges::hide() {
		foreach(EdgeControler *oneEdge, mEdges.values()) { oneEdge->hide(); }
	}
	void Edges::show() {
		foreach(EdgeControler *oneEdge, mEdges.values()) { oneEdge->show(); }
	}
	void Edges::onParentResize(QSize size) {
		foreach(EdgeControler* oneEdge, mEdges.values())
		{
			switch (oneEdge->direction())
			{
			case Jui::direction::right:
				oneEdge->setGeometry(
					size.width() - thickness - offset,
					offset + corner + gap,
					thickness,
					size.height() - 2 * offset - 2 * corner - 2 * gap
				);
				break;
			case Jui::direction::bottom:
				oneEdge->setGeometry(
					offset + corner + gap,
					size.height() - offset - thickness,
					size.width() - 2 * offset - 2 * corner - 2 * gap,
					thickness
				);
				break;
			case Jui::direction::left:
				oneEdge->setGeometry(
					offset,
					offset + corner + gap,
					thickness,
					size.height() - 2 * offset - 2 * corner - 2 * gap
				);
				break;
			case Jui::direction::top:
				oneEdge->setGeometry(
					offset + corner + gap,
					offset,
					size.width() - 2 * offset - 2 * corner - 2 * gap,
					thickness
				);
				break;
			}
		}
	}
	void Edges::onControlerPressed()
	{
		if (m_parent->isWindow()) {
			mousePressedOriginCoor = m_parent->mapToGlobal(QPoint(0, 0));
		}
		else {
			mousePressedOriginCoor = m_parent->mapToParent(QPoint(0, 0));
		}
		mousePressedParentSize = m_parent->size();
	}
	void Edges::onControlerMoved(Jui::direction dir, QPoint deltaPt)
	{
		QPoint origin(mousePressedOriginCoor);
		QSize size(mousePressedParentSize);

		switch (dir)
		{
		case Jui::direction::left:
			size.setWidth(mousePressedParentSize.width() - deltaPt.x());
			origin.setX(mousePressedOriginCoor.x() + deltaPt.x());
			m_parent->move(origin);
			break;
		case Jui::direction::right:
			size.setWidth(mousePressedParentSize.width() + deltaPt.x());
			break;

		case Jui::direction::top:
			size.setHeight(mousePressedParentSize.height() - deltaPt.y());
			origin.setY(mousePressedOriginCoor.y() + deltaPt.y());
			m_parent->move(origin);
			break;
		case Jui::direction::bottom:
			size.setHeight(mousePressedParentSize.height() + deltaPt.y());
			break;
		}
		m_parent->setFixedSize(size);
	}
}

