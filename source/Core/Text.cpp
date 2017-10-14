#include "Text.h"

namespace Jui
{
	// PureText /////////////////////////////////////////////////////

	PureText::PureText(QWidget *parent) : Canvas(parent) {
		text = "Nan";
		font_("Univers Condensed");
		flags = Qt::AlignCenter;
		displayFrame = false;
	}
	void PureText::geometry_(int x, int y, int w, int h)
	{
		//Canvas::geometry_(x, y, w, h);
		setGeometry(x, y, w, h);
		QFont f = this->font();
		f.setPixelSize(h * 5 / 6);
		setFont(f);
	}	
	void PureText::text_(QString t) {
		text = t;
		update();
	}
	void PureText::font_(QString family) {
		QFont f = this->font();
		f.setFamily(family);
		setFont(f);
		update();
	}
	void PureText::align_(Qt::Alignment f) {
		flags = f;
	}
	void PureText::displayFrame_(bool b) { displayFrame = b; }

	void PureText::paintEvent(QPaintEvent *e) {
		QPainter painter(this);
		QRect frameRect = QRect(0, 0, width() - 1, height() - 1);

		if (displayFrame) {
			painter.setPen(QColor(50, 50, 250));
			painter.drawRect(frameRect);

			painter.setPen(QColor(30, 200, 30));
			for (int i = 0; i < text.size(); ++i)
			{
				painter.drawRect(latterRect(i));
			}

			painter.setPen(QColor(130, 30, 30));
			painter.drawRect(boudingRect());
		}

		painter.setPen(QColor(200, 200, 200));
		painter.drawText(rect(), flags, text);
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
		QRect frameRect = QRect(0, 0, width() - 1, height() - 1);
		QFontMetrics fm = this->fontMetrics();
		QRect bbox = fm.boundingRect(frameRect, flags, text);
		int gapPosX = fm.width(text, index) + bbox.left();
		QLine gapLine(gapPosX, 0, gapPosX, height() - 1);
		return gapLine;
	}
	QRect PureText::gapRect(int indexFrom, int indexTo) {
		QRect frameRect = QRect(0, 0, width() - 1, height() - 1);
		QFontMetrics fm = this->fontMetrics();
		QRect bbox = fm.boundingRect(frameRect, flags, text);
		int gapPosX = fm.width(text, indexFrom);
		int rectWidth = fm.width(text, indexTo) - gapPosX;
		QRect gapRect(gapPosX + bbox.left(), 0, rectWidth, height() - 1);
		return gapRect;
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

	// LineText /////////////////////////////////////////////////////

	LineText::LineText(QWidget *parent) : PureText(parent) {
		m_cursorIndex = -1;
		deselect();
		previousText = text;
		colorFrame.value_(30, 30, 30);
		colorFrame.reciever(this);
	}

	bool LineText::hasSelection() {
		if (m_selectFrom != -1 && m_selectTo != -1) { return true; }
		return false;
	}
	void LineText::selectAll() {
		m_selectFrom = 0;
		m_selectTo = text.size();
		m_cursorIndex = text.size();
		update();
	}
	void LineText::selectFrom(int from)
	{
		m_selectFrom = from;
		m_cursorIndex = from;
		update();
	}
	void LineText::selectTo(int to)
	{
		m_selectTo = to;
		update();
	}
	void LineText::deselect() {
		m_selectFrom = -1;
		m_selectTo = -1;
		update();
	}

	void LineText::enterEvent(QEvent *event)
	{
		//qDebug() << "LineText::enterEvent";
		colorFrame.value_(200, 200, 200, 0.5);
	}
	void LineText::leaveEvent(QEvent *event)
	{
		//qDebug() << "LineText::leaveEvent";
		colorFrame.value_(50, 50, 50, 1);
	}
	void LineText::focusOutEvent(QFocusEvent *e) {
		deselect();
		m_cursorIndex = -1;
	}

	void LineText::mousePressEvent(QMouseEvent *e) {
		setFocus(Qt::MouseFocusReason);
		int mPressIndex = gapIndex(e->pos());
		if (m_cursorIndex != mPressIndex) {
			m_cursorIndex = mPressIndex;
			emit cursorChanged(mPressIndex);
			/*
			qDebug() << tr("PureText::mousePressEvent cursorIndex[%1]").arg(
				QString::number(mPressIndex)
			);
			*/
		}
		selectFrom(mPressIndex);
		selectTo(mPressIndex);
	}
	void LineText::mouseMoveEvent(QMouseEvent *e) {
		m_cursorIndex = m_selectFrom;
		selectTo(gapIndex(e->pos()));
	}
	void LineText::mouseDoubleClickEvent(QMouseEvent *e) { selectAll(); }
	void LineText::keyPressEvent(QKeyEvent *e) {

		switch (e->key())
		{
		case Qt::Key_Return:
		case Qt::Key_Enter:
			//qDebug() << "LineText::keyPressEvent(ENTER)";
			previousText = text;
			m_cursorIndex = -1;
			deselect();
			emit enterPressed();
			break;
		case Qt::Key_Escape:
			//qDebug() << "LineText::keyPressEvent(ESC)";
			text = previousText;
			m_cursorIndex = -1;
			deselect();
			break;
		case Qt::Key_Left:
			if (m_cursorIndex > 0) {
				m_cursorIndex--;
				deselect();
				emit cursorChanged(m_cursorIndex);
				//qDebug() << "LineText::keyPressEvent(LEFT)";
			}
			break;
		case Qt::Key_Right:
			if (m_cursorIndex < text.size()) {
				m_cursorIndex++;
				deselect();
				emit cursorChanged(m_cursorIndex);
				//qDebug() << "LineText::keyPressEvent(RIGHT)";
			}
			break;
		case Qt::Key_Backspace:
			if (m_cursorIndex > 0) {
				if (hasSelection())
				{
					text.remove(m_selectFrom, m_selectTo - m_selectFrom);
				}
				else
				{
					text.remove(m_cursorIndex - 1, 1);
					m_cursorIndex--;
				}
				deselect();
				emit textEdited();
				emit cursorChanged(m_cursorIndex);
			}
			break;
		case Qt::Key_Delete:
			if (hasSelection()) { text.remove(m_selectFrom, m_selectTo - m_selectFrom); }
			else { text.remove(m_cursorIndex, 1); }
			deselect();
			emit textEdited();
			break;
		default:
			if (hasSelection()) {
				text.remove(m_selectFrom, m_selectTo - m_selectFrom);
				m_cursorIndex = m_selectFrom;
			}
			text.insert(m_cursorIndex, e->text());
			m_cursorIndex++;
			deselect();
			emit cursorChanged(m_cursorIndex);
			emit textEdited();
			break;
		}
		update();
	}

	void LineText::paintEvent(QPaintEvent *e) {

		QPainter painter(this);

		if (hasFocus())
		{
			QRect frameRect = QRect(0, 0, width() - 1, height() - 1);
			painter.setPen(QColor(30, 30, 30));
			painter.drawRect(frameRect);
		}

		if (hasSelection())
		{
			painter.fillRect(gapRect(m_selectFrom, m_selectTo), QColor(50, 50, 150));
		}

		if (m_cursorIndex != -1) {
			painter.setPen(QColor(230, 30, 30));
			painter.drawLine(gapLine(m_cursorIndex));
		}

		painter.setPen(colorFrame.value());
		PureText::paintEvent(e);
	}

}