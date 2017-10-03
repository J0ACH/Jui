#include "Button.h"

namespace Jui
{

	// Button /////////////////////////////////////////////////////

	Button::Button(QWidget *parent) : QPushButton(parent) {
		colorFrame_(QColor(20, 20, 20), QColor(50, 50, 50));
		colorBackground_(QColor(0, 0, 0, 0), QColor(130, 30, 30));
		colorFrame.reciever(this);
		colorBackground.reciever(this);
		show();
	}
	void Button::colorFrame_(QColor normal, QColor over) {
		colorNormal = normal;
		colorOver = over;
		colorFrame.value_(normal);
	}
	void Button::colorBackground_(QColor off, QColor on) {
		colorOff = off;
		colorOn = on;
		colorBackground.value_(off);
	}
	void Button::enterEvent(QEvent *event)
	{
		colorFrame.value_(80, 80, 80, 0.2);
	}
	void Button::leaveEvent(QEvent *event)
	{
		colorFrame.value_(20, 20, 20, 1);
	}
	void Button::mousePressEvent(QMouseEvent *e) {
		QPushButton::mousePressEvent(e);
		if (!this->isChecked()) {
			colorBackground.value_(colorOn, 0.05);
		}
	}
	void Button::mouseReleaseEvent(QMouseEvent *e) {
		QPushButton::mouseReleaseEvent(e);
		if (!this->isChecked()) {
			colorBackground.value_(colorOff, 0.5);
		}
	}
	void Button::paintEvent(QPaintEvent *e) {
		QPainter painter(this);
		QRect frameRect = QRect(0, 0, width() - 1, height() - 1);
		QRect fillRect = QRect(0, 0, width(), height());

		painter.fillRect(QRect(5, height() - 3, width() - 10, 1), colorBackground.value());

		painter.setPen(colorFrame.value());
		painter.drawRect(frameRect);

		painter.setPen(QColor(255, 255, 255));
		painter.drawText(fillRect, Qt::AlignCenter, this->text());
	}
}

