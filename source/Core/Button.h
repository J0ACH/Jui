#ifndef BUTTON_H
#define BUTTON_H

#include "Core.h"
#include "Fade.h"
#include "Canvas.h"
#include "Text.h"

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

	// NumberBox /////////////////////////////////////////////////////

	class NumberBox : public Canvas
	{
		Q_OBJECT

	public:
		NumberBox(QWidget *parent = 0);
		void text_(QString text);
		void decimalNumbers_(int cnt);
		double value();

	signals:
		void started();
		void changed();
		void finished();

	private:
		PureText *label, *current;
		LineText *target, *fadetime;
		FadeDouble variable;
		int cntDecNums;
		qint64 startTime;

		private slots:
		void onSet();
		void onCurrentChanged();
		void onFinished();
	};

	// StringBox /////////////////////////////////////////////////////

	class StringBox : public Canvas
	{
		Q_OBJECT

	public:
		StringBox(QWidget *parent = 0);
		void label_(QString text);
		void text_(QString text);
		QString value();

	signals:
		void changed();

	private:
		PureText *label;
		LineText *txt;
		
		private slots:
		void onSet();
	};
}

#endif // BUTTON_H
