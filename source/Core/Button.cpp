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
		setPlaceholderText("vloz text");
		//text_("aaa");
		setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
		setFont(QFont("Univers Condensed", 12));
		show();

		colorText.value_(50, 50, 50);
		colorText.reciever(this);

		colorFrame.value_(50, 50, 50);
		colorFrame.reciever(this);

		connect(
			this, &QLineEdit::textChanged,
			this, &TextEdit::onTextChanged
		);
		connect(
			this, &QLineEdit::cursorPositionChanged,
			this, &TextEdit::onCursorPositionChanged
		);
		connect(
			this, &QLineEdit::selectionChanged,
			this, &TextEdit::onSelectionChanged
		);
		connect(
			this, &QLineEdit::returnPressed,
			this, &TextEdit::onReturnPressed
		);
	}
	QString TextEdit::text() { return QLineEdit::text(); }
	void TextEdit::text_(QString text) { this->setText(text); }

	void TextEdit::onTextChanged(QString text) {
		//qDebug() << tr("TextEdit::onTextChanged (%1)").arg(text);

		QFontMetrics fm = this->fontMetrics();
		textRect = fm.boundingRect(this->rect(), this->alignment(), text);

		//cursorRect = this->cursorRect();
		textLine = QRect(
			this->cursorRect().x() + textRect.left(),
			this->cursorRect().y(),
			1,
			this->cursorRect().y() + this->cursorRect().height() - 1
		);
		update();
	}
	void TextEdit::onCursorPositionChanged(int oldIndex, int newIndex) {
		/*
		cursorLine = QLine(
			QPoint(textRect.left() + cursorRect().left() + 2, cursorRect().y() + 3),
			QPoint(textRect.left() + cursorRect().left() + 2, cursorRect().height() + 2)
		);
		qDebug() << tr("TextEdit::onCursorPositionChanged [%1, %2, %3, %4]").arg(
			QString::number(cursorRect().left()),
			QString::number(cursorRect().top()),
			QString::number(cursorRect().right()),
			QString::number(cursorRect().bottom())
		);
		*/
		update();
	}
	void TextEdit::onSelectionChanged() {
		QString selText = this->selectedText();
		qDebug() << tr("TextEdit::onSelectionChanged (%1)").arg(
			selText
		);
	}
	void TextEdit::onReturnPressed() {
		qDebug() << "TextEdit::onReturnPressed";
		colorFrame.value_(200, 30, 30);
		colorFrame.value_(50, 50, 50, 1.5);
	}

	void TextEdit::enterEvent(QEvent *event)
	{
		colorText.value_(200, 200, 200, 0.5);
	}
	void TextEdit::leaveEvent(QEvent *event)
	{
		colorText.value_(50, 50, 50, 2.5);
	}

	void TextEdit::focusInEvent(QFocusEvent *e) {
		qDebug() << "TextEdit::focusInEvent";
		//this->cursorPositionAt(Point &pos)
		update();
	}

	void TextEdit::paintEvent(QPaintEvent *e) {
		QPainter painter(this);
		QRect fillRect = QRect(0, 0, width(), height());
		QRect frameRect = QRect(0, 0, width() - 1, height() - 1);

		painter.setPen(QColor(30, 30, 30));
		painter.drawRect(frameRect);

		painter.fillRect(QRect(5, height() - 3, width() - 10, 1), colorFrame.value());

		painter.setPen(QColor(30, 120, 30));
		painter.drawRect(textRect);
		//painter.fillRect(textRect, QColor(30, 120, 30));

		painter.setPen(colorText.value());
		painter.drawText(fillRect, this->alignment(), this->text());
		//painter.drawText(fillRect, this->text());

		drawCursor(painter);
	}

	void TextEdit::drawCursor(QPainter &painter) {
		QLine cursorLine(
			QPoint(textRect.left() + cursorRect().left() + 2, cursorRect().y() + 3),
			QPoint(textRect.left() + cursorRect().left() + 2, cursorRect().height() + 2)
		);

		painter.setPen(QColor(250, 30, 30));
		painter.drawLine(cursorLine);
	}


	// Button /////////////////////////////////////////////////////

	Button::Button(QWidget *parent) : QPushButton(parent) {
		colorFrame_(QColor(20, 20, 20), QColor(50, 50, 50));
		colorBackground_(QColor(0, 0, 0, 0), QColor(130, 30, 30));

		colorFrame.value_(20, 20, 20);
		colorFrame.reciever(this);

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
	QColor Button::colorBackground() { return fade_colorBackground.currentValue().value<QColor>(); }

	void Button::enterEvent(QEvent *event)
	{
		Jui::fadeVariant(fade_colorFrame, Jui::fade::in, 200);
		colorFrame.value_(80, 80, 80, 0.2);
	}
	void Button::leaveEvent(QEvent *event)
	{
		Jui::fadeVariant(fade_colorFrame, fade::out, 1000);
		colorFrame.value_(20, 20, 20, 1);
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

		painter.setPen(colorFrame.value());
		painter.drawRect(frameRect);

		painter.setPen(QColor(255, 255, 255));
		painter.drawText(fillRect, Qt::AlignCenter, this->text());
	}


}

