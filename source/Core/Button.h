#ifndef BUTTON_H
#define BUTTON_H

#include "Core.h"
#include <QPushButton>

namespace Jui
{
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