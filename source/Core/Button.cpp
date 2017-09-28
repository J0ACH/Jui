#include "Button.h"

namespace Jui
{
	// Text /////////////////////////////////////////////////////

	Text::Text(QWidget *parent) : QLabel(parent) {
		setText("NaN");
		colorText.value_(50, 50, 50);
		font_("Univers Condensed", 12);
		colorText.reciever(this);
		show();
	}

	//QString Text::text() { return QLabel::text(); }

	void Text::text_(QString text) { QLabel::setText(text); }
	void Text::font_(QString font, int size) { fontText = QFont(font, size); }
	void Text::colorText_(int r, int g, int b) { colorText.value_(r, g, b); }

	void Text::enterEvent(QEvent *event)
	{
		colorText.value_(200, 200, 200, 0.5);
	}
	void Text::leaveEvent(QEvent *event)
	{
		colorText.value_(50, 50, 50, 2.5);
	}

	void Text::paintEvent(QPaintEvent *e) {
		QPainter painter(this);
		//QRect frameRect = QRect(0, 0, width() - 1, height() - 1);
		QRect fillRect = QRect(0, 0, width(), height());

		painter.setPen(colorText.value());
		painter.setFont(fontText);
		painter.drawText(fillRect, Qt::AlignCenter, this->text());
	}

	// TextEdit /////////////////////////////////////////////////////

	TextEdit::TextEdit(QWidget *parent) : QLineEdit(parent)
	{
		text_("aaa");
		//setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
		setFont(QFont("Univers Condensed", 12));
		setFrame(false);
		show();

		colorFrame.value_(50, 50, 50);

		connect(
			this, &QLineEdit::cursorPositionChanged,
			this, &TextEdit::onCursorPositionChanged
		);
		connect(
			this, &QLineEdit::returnPressed,
			this, &TextEdit::onReturnPressed
		);
	}
	QString TextEdit::text() { return QLineEdit::text(); }
	void TextEdit::text_(QString text) { this->setText(text); }

	void TextEdit::onCursorPositionChanged(int oldIndex, int newIndex) {
		qDebug() << tr("TextEdit::onCursorPositionChanged %1 -> %2").arg(
			QString::number(oldIndex),
			QString::number(newIndex)
		);
		cursorText = QRect(
			this->cursorRect().x() + 2,
			this->cursorRect().y(),
			3,
			//this->cursorRect().x(),
			this->cursorRect().y() + this->cursorRect().height() - 1
		);
	}
	void TextEdit::onReturnPressed() {
		qDebug() << "TextEdit::onReturnPressed";
	}

	void TextEdit::paintEvent(QPaintEvent *e) {
		QPainter painter(this);
		QRect fillRect = QRect(0, 0, width(), height());
		painter.fillRect(QRect(5, height() - 3, width() - 10, 1), QColor(50, 50, 50));
		painter.setPen(QColor(200, 30, 30));
		painter.fillRect(cursorText, QColor(50, 50, 50));
		//painter.drawText(fillRect, Qt::AlignCenter, this->text());
		painter.drawText(fillRect, this->text());
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

