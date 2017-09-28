#include "Button.h"

namespace Jui
{
	// Text /////////////////////////////////////////////////////

	Text::Text(QWidget *parent) : QLabel(parent) {
		setText("NaN");
		show();
	}
	
	void Text::text_(QString text) { QLabel::setText(text); }
	QString Text::text() { return QLabel::text(); }
	
	void Text::paintEvent(QPaintEvent *e) {
		QPainter painter(this);
		//QRect frameRect = QRect(0, 0, width() - 1, height() - 1);
		QRect fillRect = QRect(0, 0, width(), height());

		painter.setPen(QColor(250, 0, 0));
		painter.drawText(fillRect, Qt::AlignCenter, this->text());
	}

	// Button /////////////////////////////////////////////////////

	Button::Button(QWidget *parent) : QPushButton(parent) {
		colorFrame_(QColor(0, 0, 0), QColor(50, 50, 50));
		colorBackground_(QColor(0, 0, 0, 0), QColor(130, 30, 30));

		connect(
			&fade_colorFrame, SIGNAL(valueChanged(QVariant)),
			this, SLOT(update())
		);
		connect(
			&fade_colorBackground, SIGNAL(valueChanged(QVariant)),
			this, SLOT(update())
		);
		show();
	}

	void Button::colorFrame_(QColor normal, QColor over) {
		fade_colorFrame.setStartValue(normal);
		fade_colorFrame.setEndValue(over);
	}
	void Button::colorBackground_(QColor off, QColor on) {
		fade_colorBackground.setStartValue(off);
		fade_colorBackground.setEndValue(on);
	}
	QColor Button::colorFrame() { return fade_colorFrame.currentValue().value<QColor>(); }
	QColor Button::colorBackground() { return fade_colorBackground.currentValue().value<QColor>(); }

	void Button::enterEvent(QEvent *event)
	{
		Jui::fadeVariant(fade_colorFrame, Jui::fade::in, 200);
	}
	void Button::leaveEvent(QEvent *event)
	{
		Jui::fadeVariant(fade_colorFrame, fade::out, 1000);
	}
	void Button::mousePressEvent(QMouseEvent *e) {
		QPushButton::mousePressEvent(e);
		if (!this->isChecked()) {
			Jui::fadeVariant(fade_colorBackground, fade::in, 50);
		}
	}
	void Button::mouseReleaseEvent(QMouseEvent *e) {
		QPushButton::mouseReleaseEvent(e);
		if (!this->isChecked()) {
			Jui::fadeVariant(fade_colorBackground, fade::out, 500);
		}
	}

	void Button::paintEvent(QPaintEvent *e) {
		QPainter painter(this);
		QRect frameRect = QRect(0, 0, width() - 1, height() - 1);
		QRect fillRect = QRect(0, 0, width(), height());

		painter.fillRect(QRect(5, height() - 3, width() - 10, 1), this->colorBackground());

		painter.setPen(this->colorFrame());
		painter.drawRect(frameRect);

		painter.setPen(QColor(255, 255, 255));
		painter.drawText(fillRect, Qt::AlignCenter, this->text());
	}


}

