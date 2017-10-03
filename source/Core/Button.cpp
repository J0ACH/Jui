#include "Button.h"

namespace Jui
{
	// PureText /////////////////////////////////////////////////////

	PureText::PureText(QWidget *parent) : QWidget(parent) {
		text = "NaIyn";
		previousText = text;
		cursorIndex = -1;
		colorFrame.reciever(this);
		colorFrame.value_(30, 30, 30);
		flags = Qt::AlignCenter;
		show();
	}
	void PureText::geometry_(int x, int y, int w, int h)
	{
		setGeometry(x, y, w, h);
		QFont f = this->font();
		f.setPixelSize(h);
		setFont(f);
	}
	void PureText::text_(QString t) {
		text = t;
		emit textChanged();
	}

	void PureText::font_(QString family) {
		QFont f;
		f.setFamily(family);
		f.setPixelSize(height());
		setFont(f);
	}
	void PureText::align_(Qt::Alignment f) {
		flags = f;
	}

	void PureText::enterEvent(QEvent *event)
	{
		//qDebug() << "PureText::enterEvent";
		colorFrame.value_(200, 200, 200, 0.5);
	}
	void PureText::leaveEvent(QEvent *event)
	{
		//qDebug() << "PureText::leaveEvent";
		colorFrame.value_(50, 50, 50, 1);
	}

	void PureText::mousePressEvent(QMouseEvent *e) {
		QWidget::mousePressEvent(e);
		setFocus(Qt::MouseFocusReason);

		int mPressIndex = gapIndex(e->pos());
		if (cursorIndex != mPressIndex) {
			cursorIndex = mPressIndex;
			emit cursorChanged(cursorIndex);
			/*
			qDebug() << tr("PureText::mousePressEvent cursorIndex[%1]").arg(
				QString::number(cursorIndex)
			);
			*/
		}

		update();
	}
	void PureText::keyPressEvent(QKeyEvent *e) {


		switch (e->key())
		{
		case Qt::Key_Return:
		case Qt::Key_Enter:
			//qDebug() << "PureText::keyPressEvent(ENTER)";
			previousText = text;
			emit enterPressed();
			cursorIndex = -1;
			break;
		case Qt::Key_Escape:
			//qDebug() << "PureText::keyPressEvent(ESC)";
			text = previousText;
			cursorIndex = -1;
			break;
		case Qt::Key_Left:
			if (cursorIndex > 0) {
				cursorIndex--;
				emit cursorChanged(cursorIndex);
				//qDebug() << "PureText::keyPressEvent(LEFT)";
			}
			break;
		case Qt::Key_Right:
			if (cursorIndex < text.size()) {
				cursorIndex++;
				emit cursorChanged(cursorIndex);
				//qDebug() << "PureText::keyPressEvent(RIGHT)";
			}
			break;
		case Qt::Key_Backspace:
			if (cursorIndex > 0) {
				text.remove(cursorIndex - 1, 1);
				cursorIndex--;
				emit textEdited();
				emit cursorChanged(cursorIndex);
				//qDebug() << "PureText::keyPressEvent(BACK)";
			}
			break;
		case Qt::Key_Delete:
			text.remove(cursorIndex, 1);
			emit textEdited();
			//qDebug() << "PureText::keyPressEvent(DEL)";
			break;
		default:
			qDebug() << tr("PureText::keyPressEvent(%1)").arg(e->text());
			text.insert(cursorIndex, e->text());
			cursorIndex++;
			emit cursorChanged(cursorIndex);
			emit textEdited();
			break;
		}
		update();
	}

	void PureText::paintEvent(QPaintEvent *e) {
		QPainter painter(this);
		QRect frameRect = QRect(0, 0, width() - 1, height() - 1);
		QRect fillRect = QRect(0, 0, width(), height());

		painter.setPen(colorFrame.value());
		painter.drawRect(frameRect);

		painter.setPen(QColor(200, 200, 200));
		painter.setFont(font());
		painter.drawText(this->rect(), flags, text);

		/*
		painter.setPen(QColor(30, 200, 30));
		for (int i = 0; i < text.size(); ++i)
		{
			painter.drawRect(latterRect(i));
		}
		painter.setPen(QColor(130, 30, 30));
		painter.drawRect(boudingRect());
		*/
		if (cursorIndex != -1) {
			painter.setPen(QColor(230, 30, 30));
			painter.drawLine(gapLine(cursorIndex));
		}
	}

	QRect PureText::boudingRect() {
		QFontMetrics fm = this->fontMetrics();
		QRect bbox = fm.boundingRect(rect(), flags, text);
		return bbox;
	}
	QRect PureText::latterRect(int index) {
		QFontMetrics fm = this->fontMetrics();
		QRect bbox = fm.boundingRect(rect(), flags, text);
		int latterPosX = fm.width(text, index);
		int latterWidth = fm.width(text, index + 1) - latterPosX;
		QRect latterRect(latterPosX + bbox.left(), 0, latterWidth, height() - 1);
		return latterRect;
	}
	QLine PureText::gapLine(int index) {
		QFontMetrics fm = this->fontMetrics();
		QRect bbox = fm.boundingRect(rect(), flags, text);
		int gapPosX = fm.width(text, index) + bbox.left();
		QLine gapLine(gapPosX, 0, gapPosX, height() - 1);
		return gapLine;
	}
	int PureText::latterIndex(QPoint pt) {
		for (int i = 0; i < text.size(); ++i)
		{
			if (latterRect(i).contains(pt)) { return(i); }
		}
		return -1;
	}
	int PureText::gapIndex(QPoint pt) {
		for (int i = 0; i < text.size(); ++i)
		{
			int centerX = latterRect(i).center().x();
			if (latterRect(i).contains(pt)) {
				if (pt.x() < centerX) { return(i); }
				if (pt.x() >= centerX) { return(i + 1); };
			}
		}
		if (pt.x() > latterRect(text.size() - 1).right()) { return(text.size()); }
		if (pt.x() < latterRect(0).left()) { return 0; }
		return -1;
	}

	// Text /////////////////////////////////////////////////////

	Text::Text(QWidget *parent) : QLabel(parent) {
		setText("NaN");
		colorText.value_(50, 50, 50);
		font_("Univers Condensed", 12);
		colorText.reciever(this);
		show();
	}
	void Text::text_(QString text) {
		QLabel::setText(text);
		colorText.value_(250, 50, 50);
		colorText.value_(50, 50, 50, 2);
	}
	void Text::font_(QString family, int size) { fontText = QFont(family, size); }
	void Text::colorText_(int r, int g, int b) { colorText.value_(r, g, b); }
	void Text::paintEvent(QPaintEvent *e) {
		QPainter painter(this);
		//QRect frameRect = QRect(0, 0, width() - 1, height() - 1);
		QRect fillRect = QRect(0, 0, width(), height());

		painter.setPen(colorText.value());
		painter.setFont(fontText);
		painter.drawText(fillRect, Qt::AlignCenter, this->text());
	}

	// TextEdit /////////////////////////////////////////////////////

	TextEdit::TextEdit(QWidget *parent) : QLineEdit(parent),
		fontDim(this->fontMetrics())
	{
		setPlaceholderText("vloz text");
		//text_("aaa");
		setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
		//setFont(QFont("Univers Condensed", 12));
		font_("Univers Condensed", 12);
		show();

		colorText.value_(50, 50, 50);
		colorText.reciever(this);

		colorFrame.value_(50, 50, 50);
		colorFrame.reciever(this);

		textRect = fontDim.boundingRect(this->rect(), this->alignment(), this->text());

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
	void TextEdit::font_(QString family, int size) {
		QFont font = QFont(family, size);
		setFont(font);
		fontDim = fontMetrics();
	}

	void TextEdit::onTextChanged(QString text) {
		qDebug() << tr("TextEdit::onTextChanged (%1)").arg(text);

		textRect = fontDim.boundingRect(this->rect(), this->alignment(), text);

		textLine = QRect(
			this->cursorRect().x() + textRect.left(),
			this->cursorRect().y(),
			1,
			this->cursorRect().y() + this->cursorRect().height() - 1
		);

		for (int i = 0; i <= this->text().size(); ++i)
		{
			letterPoint(i);
		}

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
		QLineEdit::focusInEvent(e);
		//setFocus(Qt::MouseFocusReason);
		update();
	}
	void TextEdit::focusOutEvent(QFocusEvent *e) {
		qDebug() << "TextEdit::focusOutEvent";
		QLineEdit::focusOutEvent(e);
		update();
	}

	void TextEdit::mousePressEvent(QMouseEvent *e) {
		//QLineEdit::mousePressEvent(e);
		int latterIndex = cursorPositionAt(QPoint(e->x() - textRect.left(), e->y()));
		qDebug() << tr("TextEdit::mousePressEvent cursorPosition = %1").arg(
			QString::number(latterIndex)
		);
		QLineEdit::setCursorPosition(latterIndex);
		update();
	}
	void TextEdit::mouseReleaseEvent(QMouseEvent *e) {
		QLineEdit::mouseReleaseEvent(e);
		/*
		int latterIndex = cursorPositionAt(QPoint(e->x() - textRect.left(), e->y()));
		qDebug() << tr("TextEdit::mouseReleaseEvent cursorPosition = %1").arg(
			QString::number(latterIndex)
		);
		QLineEdit::setCursorPosition(latterIndex);
		update();
		*/
	}
	void TextEdit::mouseDoubleClickEvent(QMouseEvent *e) {
		//QLineEdit::mouseDoubleClickEvent(e);
		selectAll();
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
		if (hasFocus())
		{
			drawCursor(painter);
		};

	}

	QPoint TextEdit::letterPoint(int index) {
		QStringRef subText(&this->text(), 0, index);
		QRect textR = fontDim.boundingRect(this->rect(), this->alignment(), subText.toString());
		int distanceX = textR.width();
		qDebug() << tr("TextEdit::letterPoint subText %1 = %2").arg(
			subText.toString(),
			QString::number(distanceX)
		);
		return QPoint(distanceX, textR.top());
	}

	void TextEdit::drawSelection(QPainter &painter) {
		int selStartIndex = selectionStart();
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

