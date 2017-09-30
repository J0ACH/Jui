#ifndef BUTTON_H
#define BUTTON_H

#include "Fade.h"
#include "Core.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace Jui
{

	// Text /////////////////////////////////////////////////////

	class Text : public QLabel
	{
	public:
		Text(QWidget *parent = 0);

		//QString text();

		void text_(QString text);
		void font_(QString font, int size);
		void colorText_(int r, int g, int b);

	protected:
		void enterEvent(QEvent *e) override;
		void leaveEvent(QEvent *e) override;
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

	protected:
		void paintEvent(QPaintEvent *e) override;
		
	private:
		void onTextChanged(QString);
		void onCursorPositionChanged(int, int);
		void onSelectionChanged();
		void onReturnPressed();
		
		QRect textRect, textLine, cursorText;
		QLine cursorLine;
		FadeColor colorFrame;
	};
	

	// Button /////////////////////////////////////////////////////

	class Button : public QPushButton
	{

	public:
		Button(QWidget *parent = 0);

		void colorFrame_(QColor normal, QColor over);
		void colorBackground_(QColor off, QColor on);
		QColor colorFrame();
		QColor colorBackground();

	protected:
		void enterEvent(QEvent *e) override;
		void leaveEvent(QEvent *e) override;
		void mousePressEvent(QMouseEvent *e) override;
		void mouseReleaseEvent(QMouseEvent *e) override;
		void paintEvent(QPaintEvent *e) override;

	private:
		QVariantAnimation fade_colorFrame, fade_colorBackground;
	};
}

#endif // BUTTON_H