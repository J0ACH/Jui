#include "Controls.h"

namespace Jui
{
	// Button /////////////////////////////////////////////////////

	Button::Button(QWidget *parent) : QWidget(parent) {
		isPressable = false;
		isChecked = false;
		text = "OFF";
		colorFrame.value_(QColor(0, 0, 0, 0));
		colorImage.value_(100, 100, 100);
		colorBackground.value_(QColor(0, 0, 0, 0));

		connect(
			&colorFrame, SIGNAL(changed()),
			this, SLOT(update())
		);
		connect(
			&colorBackground, SIGNAL(changed()),
			this, SLOT(update())
		);
	}
	void Button::label_(QString txt) { text = txt; }
	void Button::pressable_(bool b) { isPressable = b; }
	void Button::icon_(const char* img, int offset) {
		icon = QImage(img);
		iconOffset = offset;
	}
	void Button::symbol_(const char* code, int size) {
		setFont(QFont("Segoe MDL2 Assets", size));
		text = u8"\uE106";
	}

	void Button::enterEvent(QEvent *e) {
		colorFrame.value_(200, 200, 200, 0.2);
		colorImage.value_(200, 200, 200, 0.2);
		colorBackground.value_(250, 0, 0, 0.1);
	}
	void Button::leaveEvent(QEvent *e) {
		colorFrame.value_(QColor(0, 0, 0, 0), 1);
		colorImage.value_(100, 100, 100, 1);
		colorBackground.value_(QColor(0, 0, 0, 0), 0.5);
	}
	void Button::mousePressEvent(QMouseEvent *e) {
		if (!isChecked) {
			isChecked = true;
			colorBackground.value_(120, 20, 20, 0.05);
			text = "ON";
		}
		else
		{
			isChecked = false;
			colorBackground.value_(QColor(0, 0, 0, 0), 0.05);
			text = "OFF";
		}
		emit pressed();
	}
	void Button::mouseReleaseEvent(QMouseEvent *e) {
		if (isChecked) {
			if (!isPressable) {
				isChecked = false;
				colorBackground.value_(QColor(0, 0, 0, 0), 0.5);
				text = "OFF";
			}
		}
	}

	void Button::paintEvent(QPaintEvent *e) {
		QPainter painter(this);
		QColor textColor;

		//QRect frameRect = QRect(0, 0, width() - 1, height() - 1);
		//QRect fillRect = QRect(0, 0, width(), height());

		painter.fillRect(rect(), colorBackground);
		//painter.fillRect(fillRect, QColor(250,30,30));



		if (icon.isNull()) {

			if (parentWidget()->hasFocus()) { textColor = palette().color(QPalette::ColorGroup::Active, QPalette::ColorRole::Text); }
			else { textColor = palette().color(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text); }
			QTextOption opt = QTextOption(Qt::AlignCenter);
			painter.setPen(textColor);
			//painter.drawRect(frameRect);
			painter.drawText(rect(), text, opt);
		}
		else {
			float moveX = (this->width() - icon.width()) / 2;
			float moveY = (this->height() - icon.height()) / 2;

			QRectF target(moveX, moveY, icon.width(), icon.height());
			QRectF source(0, 0, icon.width(), icon.height());

			QImage renderedIcon(icon);
			renderedIcon.fill(colorImage);
			renderedIcon.setAlphaChannel(icon);
			painter.drawImage(target, renderedIcon, source);  // draw image to QWidget
		}
		/*
		*/
	}

}