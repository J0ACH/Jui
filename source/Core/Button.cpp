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
		backG->color_(QColor(20, 20, 20));
		this->addLayer(backG);

		LayerFrame *frame = new LayerFrame();
		frame->color_(250, 30, 30);
		this->addLayer(frame);
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

		this->colorFrame_(QColor(30, 30, 30), QColor(230, 30, 30));
		this->colorBackground_(QColor(50, 20, 20), QColor(200, 30, 30));
		
		connect(
			&fade_colorFrame, SIGNAL(valueChanged(QVariant)),
			this, SLOT(update())
		);
		connect(
			&fade_colorBackground, SIGNAL(valueChanged(QVariant)),
			this, SLOT(update())
		);
	}

	void Button2::colorFrame_(QColor normal, QColor over) {
		fade_colorFrame.setStartValue(normal);
		fade_colorFrame.setEndValue(over);
	}
	void Button2::colorBackground_(QColor off, QColor on) {
		fade_colorBackground.setStartValue(off);
		fade_colorBackground.setEndValue(on);
	}
	QColor Button2::colorFrame() { return fade_colorFrame.currentValue().value<QColor>(); }
	QColor Button2::colorBackground() { return fade_colorBackground.currentValue().value<QColor>(); }

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

		this->fadeVariant(fade_colorFrame, fade::in, 500);
		update();
	}
	void Button2::leaveEvent(QEvent *event)
	{
		this->fadeVariant(fade_colorFrame, fade::out, 2000);

		switch (m_state)
		{
		case state::offOver:
			m_state = state::offOut;
			break;
		case state::onOver:
			m_state = state::onOut;
			break;
		}

		update();
	}
	void Button2::mousePressEvent(QMouseEvent *e) {
		prev_state = m_state;
		m_state = state::press;
		
		QPushButton::mousePressEvent(e);
		if (!this->isChecked()) {
			this->fadeVariant(fade_colorBackground, fade::in, 100);
		}
		update();
	}
	void Button2::mouseReleaseEvent(QMouseEvent *e) {
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
		QPushButton::mouseReleaseEvent(e);

		if (!this->isChecked()) {
			this->fadeVariant(fade_colorBackground, fade::out, 250);
		}		
		update();
	}

	void Button2::paintEvent(QPaintEvent *e) {
		QPainter painter(this);
		QRect frameRect = QRect(0, 0, width() - 1, height() - 1);
		QRect fillRect = QRect(0, 0, width(), height());;

		painter.fillRect(fillRect, this->colorBackground());

		painter.setPen(this->colorFrame());
		painter.drawRect(frameRect);

		painter.setPen(QColor(255, 255, 255));
		painter.drawText(
			0, 0, this->width(), this->height(), Qt::AlignCenter,
			this->text()
		);
	}

	void Button2::fadeVariant(QVariantAnimation &var, Button2::fade fade, int duration) {

		if (var.state() == QAbstractAnimation::State::Running) { var.pause(); }
		var.setDuration(duration);
		switch (fade)
		{
		case Button2::fade::in:
			var.setDirection(QVariantAnimation::Direction::Forward);
			break;
		case Button2::fade::out:
			var.setDirection(QVariantAnimation::Direction::Backward);
			break;
		}

		switch (var.state())
		{
		case QAbstractAnimation::State::Paused:
			var.resume();
			break;
		default:
			var.start();
			break;
		}

	}

}

