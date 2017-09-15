#include "Button.h"

namespace Jui
{

	Button::Button(Canvas *parent) :
		Canvas(parent)
	{
		this->init();
	}
	Button::Button(Canvas *parent, int x, int y, int width, int height) :
		Canvas(parent, x, y, width, height)
	{
		this->init();
	}

	void Button::init()
	{
		intCounter = -1;
		maxCounter = -1;

		connect(
			this, SIGNAL(actMousePressed(Canvas*, QPoint)),
			this, SLOT(prOnPressed())
		);

		LayerBackground *backG = new LayerBackground();
		backG->background_(QColor(30, 30, 90));
		this->addLayer(backG);
		/*
		connect(
			this, SIGNAL(actPressed(Button*)),
			this, SLOT(changed())
		);
		*/
	}

	void Button::addState(QString name) {
		qDebug() << tr("Button::setStateName %2 [%1]").arg(
			QString::number(stateNames.size()),
			name
		);
		stateNames.append(name);
		maxCounter++;
		this->update();
	}

	int Button::getState() { return intCounter; }
	QString Button::getStateName() {
		QString currentName(stateNames.value(intCounter, "NaN"));
		return currentName;
	}

	void Button::setStateCounter(int cnt) {
		intCounter = cnt;
		if (intCounter > maxCounter) intCounter = maxCounter;
	}

	/*
	void Button::draw(QPainter &painter) {
		painter.setPen(QColor(200, 30, 30));
		painter.drawText(
			0, 0, this->width(), this->height(), Qt::AlignCenter,
			this->getStateName()
		);
	}
	*/

	void Button::prOnPressed() {
		intCounter++;
		if (intCounter > maxCounter) intCounter = 0;
		qDebug() << tr("Button::onPress %1 [%2]").arg(
			QString::number(intCounter),
			this->getStateName()
		);
		emit actPressed(this);
	}
	Button::~Button()
	{
		qDebug("Button closed");
	}


	// Button2 /////////////////////////////////

	Button2::Button2(QWidget *parent) : QPushButton(parent) {
		m_state = state::offOut;
	}

	void Button2::enterEvent(QEvent *event)
	{
		switch (m_state)
		{
		case state::offOut:
			m_state = state::offOver;
			break;
		case state::onOut:
			m_state = state::onOver;
			break;
		}
		this->update();
	}
	void Button2::leaveEvent(QEvent *event)
	{
		switch (m_state)
		{
		case state::offOver:
			m_state = state::offOut;
			break;
		case state::onOver:
			m_state = state::onOut;
			break;
		}
		this->update();
	}

	void Button2::mousePressEvent(QMouseEvent *event) {
		prev_state = m_state;
		m_state = state::press;
		update();
	}
	void Button2::mouseReleaseEvent(QMouseEvent *event) {
		switch (prev_state)
		{
		case state::offOver:
			if (!isFlat()) { m_state = state::onOver; }
			else { m_state = state::offOver; }
			break;
		case state::onOver:
			m_state = state::offOver;
			break;
		}
		this->update();
	}

	void Button2::paintEvent(QPaintEvent *e) {
		QPainter painter(this);
		QRect frameRect = QRect(0, 0, width(), height());
		QRect fillRect = QRect(0, 0, width() - 1, height() - 1);

		switch (m_state)
		{
		case state::offOut:
			draw_OffOut(&painter);
			break;
		case state::offOver:
			draw_OffOver(&painter);
			break;
		case state::press:
			draw_Press(&painter);
			break;
		case state::onOut:
			draw_OnOut(&painter);
			break;
		case state::onOver:
			draw_OnOver(&painter);
			break;
		}

		painter.setPen(QColor(255, 255, 255));
		painter.drawText(
			0, 0, this->width(), this->height(), Qt::AlignCenter,
			this->text()
		);
	}

	void Button2::draw_OffOut(QPainter* painter) {
		painter->setPen(QColor(30, 30, 30));
		painter->drawRect(QRect(0, 0, width() - 1, height() - 1));
	}
	void Button2::draw_OffOver(QPainter* painter) {
		painter->setPen(QColor(150, 150, 150));
		painter->drawRect(QRect(0, 0, width() - 1, height() - 1));
	}
	void Button2::draw_Press(QPainter* painter) {
		painter->fillRect(QRect(0, 0, width(), height()), QColor(250, 50, 50));
	}
	void Button2::draw_OnOut(QPainter* painter) {
		painter->fillRect(QRect(0, 0, width(), height()), QColor(100, 30, 30));
	}
	void Button2::draw_OnOver(QPainter* painter) {
		painter->fillRect(QRect(0, 0, width(), height()), QColor(100, 30, 30));
		painter->setPen(QColor(150, 150, 150));
		painter->drawRect(QRect(0, 0, width() - 1, height() - 1));
	}


}

