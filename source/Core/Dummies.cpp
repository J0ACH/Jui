#include "Dummies.h"

namespace Jui
{
	// Header /////////////////////////////////////////////////////

	Header::Header(QWidget *parent) : Button(parent),
		m_parent(parent),
		m_text(new PureText(this))
	{
		//Jui::loadFonts();
		colorBackground_(QColor(0, 0, 0, 0), QColor(120, 20, 20));
		m_text->font_("Univers Condensed");
		m_text->text_(parent->objectName());
		m_text->align_(Qt::AlignVCenter | Qt::AlignLeft);
		thickness = 30;
		move(1, 1);
		fitSize();
		m_parent->installEventFilter(this);
	}
	void Header::font_(QString family) { m_text->font_(family); }
	void Header::fitSize() {
		setFixedSize(m_parent->size().width() - 2, thickness);
		m_text->geometry_(20, 6, m_parent->size().width() - 2, thickness - 12);
	}
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
		painter.fillRect(rect(), colorBackground.value());
	}

	// EdgeControler /////////////////////////////////////////////////////

	EdgeControler::EdgeControler(QWidget *parent, Jui::direction dir) :
		Button(parent),
		m_direction(dir)
	{
		colorFrame_(QColor(20, 20, 20, 0), QColor(60, 60, 60));
	}
	Jui::direction EdgeControler::direction() { return m_direction; }
	void EdgeControler::mousePressEvent(QMouseEvent *e)
	{
		colorFrame_(QColor(60, 60, 60), QColor(120, 20, 20));
		Button::mousePressEvent(e);
		mousePressedGlobalCoor = e->globalPos();
	}
	void EdgeControler::mouseReleaseEvent(QMouseEvent *e)
	{
		colorFrame_(QColor(20, 20, 20, 0), QColor(60, 60, 60));
		Button::mouseReleaseEvent(e);
	}
	void EdgeControler::mouseMoveEvent(QMouseEvent *e)
	{
		QPoint deltaPt(
			e->globalPos().x() - mousePressedGlobalCoor.x(),
			e->globalPos().y() - mousePressedGlobalCoor.y()
		);
		emit actControlerMoved(m_direction, deltaPt);
	}
	void EdgeControler::paintEvent(QPaintEvent *event)
	{
		QPainter painter(this);
		painter.setPen(colorFrame.value());
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
		thickness = 10;
		offset = 1;
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

		fitSize();
		m_parent->installEventFilter(this);

		foreach(EdgeControler *oneEdge, mEdges.values())
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
	}
	bool Edges::eventFilter(QObject *object, QEvent *e)
	{
		switch (e->type())
		{
		case QEvent::Type::Resize:
			fitSize();
			break;
		};
		return false;
	}
	void Edges::fitSize()
	{
		foreach(EdgeControler* oneEdge, mEdges.values())
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

