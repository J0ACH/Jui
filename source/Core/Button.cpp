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
		connect(
			this, SIGNAL(actPressed(Button*)),
			this, SLOT(changed())
		);
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

	void Button::changed() { }

	void Button::paintEvent(QPaintEvent *event)
	{
		Canvas::paintEvent(event);
		QPainter painter(this);

		painter.setPen(QColor(200, 30, 30));
		painter.drawText(
			0, 0, this->width(), this->height(), Qt::AlignCenter,
			this->getStateName()
		);
	}

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
}

