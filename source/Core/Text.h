#ifndef TEXT_H
#define TEXT_H

#include "Core.h"
#include "Fade.h"
#include "Canvas.h"

namespace Jui
{

	// PureText /////////////////////////////////////////////////////

	class PureText : public Canvas
	{

	public:
		PureText(QWidget *parent = 0);

		void geometry_(int x, int y, int w, int h);
		void text_(QString text);
		void font_(QString family);
		void align_(Qt::Alignment f);
		void displayFrame_(bool b);

		QString text;

	protected:
		QRect boudingRect();
		QRect latterRect(int index);
		QRect latterRect(int indexFrom, int indexTo);
		QLine gapLine(int index);
		QRect gapRect(int indexFrom, int indexTo);
		int latterIndex(QPoint pt);
		int gapIndex(QPoint pt);

		void paintEvent(QPaintEvent *e) override;

	private:
		Qt::Alignment flags;
		bool displayFrame;
	};


	// LineText /////////////////////////////////////////////////////

	class LineText : public PureText
	{
		Q_OBJECT

	public:
		LineText(QWidget *parent = 0);

		bool hasSelection();
		void selectAll();
		void selectFrom(int from);
		void selectTo(int to);
		void deselect();

	signals:
		void textChanged();
		void textEdited();
		void cursorChanged(int idGap);
		void selectionChanged(int from, int to);
		void enterPressed();

	protected:
		void enterEvent(QEvent *e) override;
		void leaveEvent(QEvent *e) override;
		void focusOutEvent(QFocusEvent *e) override;
		void mousePressEvent(QMouseEvent *e) override;
		void mouseMoveEvent(QMouseEvent *e) override;
		void mouseDoubleClickEvent(QMouseEvent *e) override;
		void keyPressEvent(QKeyEvent *e) override;
		void paintEvent(QPaintEvent *e) override;
	private:

		int m_cursorIndex, m_selectFrom, m_selectTo;
		QString previousText;
		FadeColor colorFrame;
	};
}

#endif // TEXT_H