#ifndef BUTTON_H
#define BUTTON_H

#include "Core.h"
#include "Fade.h"

namespace Jui
{

	// Button /////////////////////////////////////////////////////

	class Button : public QPushButton
	{

	public:
		Button(QWidget *parent = 0);

		void colorFrame_(QColor normal, QColor over);
		void colorBackground_(QColor off, QColor on);
		void icon_(QImage img, int offset);
		
	protected:
		void enterEvent(QEvent *e) override;
		void leaveEvent(QEvent *e) override;
		void mousePressEvent(QMouseEvent *e) override;
		void mouseReleaseEvent(QMouseEvent *e) override;
		void paintEvent(QPaintEvent *e) override;

		FadeColor colorFrame, colorBackground;
	private:
		QColor colorNormal, colorOver, colorOff, colorOn;
		QImage icon;
		int iconOffset;
	};
}

#endif // BUTTON_H