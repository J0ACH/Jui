#include "Text.h"

namespace Jui
{
	// PureText /////////////////////////////////////////////////////

	PureText::PureText(QWidget *parent) : QWidget(parent) {
		text = "NaIyn";
		cursorIndex = -1;
		selectFrom = -1;
		selectTo = -1;
		flags = Qt::AlignCenter;
		show();
	}
	void PureText::geometry_(int x, int y, int w, int h)
	{
		setGeometry(x, y, w, h);
		QFont f = this->font();
		f.setPixelSize(h * 5 / 6);
		setFont(f);
	}
	void PureText::text_(QString t) {
		text = t;
		emit textChanged();
	}

	void PureText::font_(QString family) {
		QFont f = this->font();
		f.setFamily(family);
		setFont(f);
	}
	void PureText::align_(Qt::Alignment f) {
		flags = f;
	}

	bool PureText::hasSelection() {
		if (selectFrom != -1 && selectTo != -1) { return true; }
		return false;
	}
	void PureText::selectAll() {
		selectFrom = 0;
		selectTo = text.size();
		cursorIndex = text.size();
		update();
	}
	void PureText::select(int from, int to)
	{
		selectFrom = from;
		selectTo = to;
		cursorIndex = from;
		update();
	}
	void PureText::deselect() {
		selectFrom = -1;
		selectTo = -1;
		update();
	}

	void PureText::paintEvent(QPaintEvent *e) {
		QPainter painter(this);
		QRect frameRect = QRect(0, 0, width() - 1, height() - 1);

		if (hasSelection())
		{
			painter.fillRect(latterRect(selectFrom, selectTo), QColor(50, 50, 150));
		}

		painter.setPen(QColor(50, 50, 250));
		painter.drawRect(frameRect);

		painter.setPen(QColor(200, 200, 200));
		//painter.setFont(font());
		painter.drawText(rect(), flags, text);

		painter.setPen(QColor(30, 200, 30));
		for (int i = 0; i < text.size(); ++i)
		{
			painter.drawRect(latterRect(i));
		}
		painter.setPen(QColor(130, 30, 30));
		painter.drawRect(boudingRect());
		/*
		*/

		if (cursorIndex != -1) {
			painter.setPen(QColor(230, 30, 30));
			painter.drawLine(gapLine(cursorIndex));
		}
	}

	QRect PureText::boudingRect() {
		QRect frameRect = QRect(0, 0, width() - 1, height() - 1);
		QFontMetrics fm = this->fontMetrics();
		QRect bbox = fm.boundingRect(frameRect, flags, text);
		return bbox;
	}
	QRect PureText::latterRect(int index) {
		return PureText::latterRect(index, index);
	}
	QRect PureText::latterRect(int indexFrom, int indexTo) {
		QRect frameRect = QRect(0, 0, width() - 1, height() - 1);
		QFontMetrics fm = this->fontMetrics();
		QRect bbox = fm.boundingRect(frameRect, flags, text);
		int latterPosX = fm.width(text, indexFrom);
		int latterWidth = fm.width(text, indexTo + 1) - latterPosX;
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

	QLine PureText::upperLine() {
		QFontMetrics fm = this->fontMetrics();
		fm.ascent();
		return QLine();
	}

	// LineText /////////////////////////////////////////////////////

	LineText::LineText(QWidget *parent) : PureText(parent) {
		previousText = text;
		colorFrame.reciever(this);
		colorFrame.value_(30, 30, 30);
	}
	void LineText::enterEvent(QEvent *event)
	{
		qDebug() << "LineText::enterEvent";
		colorFrame.value_(200, 200, 200, 0.5);
	}
	void LineText::leaveEvent(QEvent *event)
	{
		qDebug() << "LineText::leaveEvent";
		colorFrame.value_(50, 50, 50, 1);
	}

	void LineText::mousePressEvent(QMouseEvent *e) {
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
		selectFrom = latterIndex(e->pos());
		selectTo = -1;
		update();
	}
	void LineText::mouseMoveEvent(QMouseEvent *e) {
		cursorIndex = selectFrom;
		selectTo = latterIndex(e->pos());
		//selectTo = gapIndex(e->pos());
		update();
	}
	void LineText::mouseDoubleClickEvent(QMouseEvent *e) { selectAll(); }
	void LineText::keyPressEvent(QKeyEvent *e) {

		switch (e->key())
		{
		case Qt::Key_Return:
		case Qt::Key_Enter:
			//qDebug() << "PureText::keyPressEvent(ENTER)";
			previousText = text;
			cursorIndex = -1;
			deselect();
			emit enterPressed();
			break;
		case Qt::Key_Escape:
			//qDebug() << "PureText::keyPressEvent(ESC)";
			text = previousText;
			cursorIndex = -1;
			deselect();
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
				deselect();
				emit textEdited();
				emit cursorChanged(cursorIndex);
				//qDebug() << "PureText::keyPressEvent(BACK)";
			}
			break;
		case Qt::Key_Delete:
			if (hasSelection())
			{
				text.remove(selectFrom, selectTo - selectFrom + 1);
			}
			else { text.remove(cursorIndex, 1); }
			deselect();
			emit textEdited();
			//qDebug() << "PureText::keyPressEvent(DEL)";
			break;
		default:
			//qDebug() << tr("PureText::keyPressEvent(%1)").arg(e->text());

			qDebug() << tr("PureText::keyPressEvent hasSelection[%1] from[%2] to[%3]").arg(
				QString::number(hasSelection()),
				QString::number(selectFrom),
				QString::number(selectTo)
			);

			if (hasSelection()) {
				text.remove(selectFrom, selectTo - selectFrom + 1);
			}
			text.insert(cursorIndex, e->text());
			cursorIndex++;
			deselect();
			emit cursorChanged(cursorIndex);
			emit textEdited();
			break;
		}
		update();
	}

	void LineText::paintEvent(QPaintEvent *e) {
		PureText::paintEvent(e);

		QPainter painter(this);
		QRect frameRect = QRect(0, 0, width() - 1, height() - 1);

		painter.setPen(colorFrame.value());
		//painter.drawRect(frameRect);

	}

}