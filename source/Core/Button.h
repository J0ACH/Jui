#ifndef BUTTON_H
#define BUTTON_H

#include "Fade.h"
#include "Core.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace Jui
{

	// PureText /////////////////////////////////////////////////////

	class PureText : public QWidget
	{
		Q_OBJECT
	public:
		PureText(QWidget *parent = 0);

		void geometry_(int x, int y, int w, int h);
		void text_(QString text);
		void font_(QString family);
		void align_(Qt::Alignment f);
		
	signals:
		void textChanged();
		void textEdited();
		void cursorChanged(int idGap);

	protected:
		void enterEvent(QEvent *e) override;
		void leaveEvent(QEvent *e) override;
		void mousePressEvent(QMouseEvent *e) override;
		void keyPressEvent(QKeyEvent *e) override;
		void paintEvent(QPaintEvent *e) override;

		QRect boudingRect();
		QRect latterRect(int index);
		QLine gapLine(int index);
		int latterIndex(QPoint pt);
		int gapIndex(QPoint pt);
	
	private:
		QString text;
		int cursorIndex;
		Qt::Alignment flags;
		FadeColor colorFrame;
	};


	// Text /////////////////////////////////////////////////////

	class Text : public QLabel
	{
	public:
		Text(QWidget *parent = 0);
		void text_(QString text);
		void font_(QString family, int size);
		void colorText_(int r, int g, int b);

	protected:
		void paintEvent(QPaintEvent *e) override;

	private:
		FadeColor colorText;
		QFont fontText;
	};

	// TextEdit /////////////////////////////////////////////////////

	class TextEdit : public QLineEdit
	{
	public:
		TextEdit(QWidget *parent = 0);

		QString text();
		void text_(QString text);
		void font_(QString family, int size);

	protected:
		void enterEvent(QEvent *e) override;
		void leaveEvent(QEvent *e) override;
		void focusInEvent(QFocusEvent *e) override;
		void focusOutEvent(QFocusEvent *e) override;
		void mousePressEvent(QMouseEvent *e) override;
		void mouseReleaseEvent(QMouseEvent *e) override;
		void mouseDoubleClickEvent(QMouseEvent *e) override;
		void paintEvent(QPaintEvent *e) override;

	private:
		void onTextChanged(QString);
		void onCursorPositionChanged(int, int);
		void onSelectionChanged();
		void onReturnPressed();

		QPoint letterPoint(int index);

		void drawSelection(QPainter &painter);
		void drawCursor(QPainter &painter);

		QFontMetrics fontDim;
		QRect textRect, textLine;
		//QLine cursorLine;
		FadeColor colorText, colorFrame;
	};


	// Button /////////////////////////////////////////////////////

	class Button : public QPushButton
	{

	public:
		Button(QWidget *parent = 0);

		void colorFrame_(QColor normal, QColor over);
		void colorBackground_(QColor off, QColor on);
		QColor colorBackground();

	protected:
		void enterEvent(QEvent *e) override;
		void leaveEvent(QEvent *e) override;
		void mousePressEvent(QMouseEvent *e) override;
		void mouseReleaseEvent(QMouseEvent *e) override;
		void paintEvent(QPaintEvent *e) override;

		FadeColor colorFrame;
	private:
		QVariantAnimation fade_colorFrame, fade_colorBackground;
	};
}

#endif // BUTTON_H