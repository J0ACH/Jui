#ifndef CONTROLS_H
#define CONTROLS_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include "Fade.h"

namespace Jui
{
	// Button /////////////////////////////////////////////////////

	class Button : public QWidget
	{
		Q_OBJECT

	public:
		Button(QWidget *parent = 0);

		void label_(QString txt);
		void pressable_(bool b);
		void icon_(const char* img, int offset = 0);
		void symbol_(const char* code, int size = 8);

		//void backgroundColor_(QColor color, double fadeTime);

	signals:
		void pressed();

	protected:
		void enterEvent(QEvent *e) override;
		void leaveEvent(QEvent *e) override;
		void mousePressEvent(QMouseEvent *e) override;
		void mouseReleaseEvent(QMouseEvent *e) override;

		void paintEvent(QPaintEvent *e) override;

	private:
		QString text;
		bool isPressable, isChecked;
		FadeColor colorFrame, colorImage, colorBackground;
		QImage icon;
		int iconOffset;
	};

}

#endif // CONTROLS_H