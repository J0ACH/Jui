#ifndef BUTTON_H
#define BUTTON_H

#include "Core.h"
#include "Fade.h"
#include "Text.h"

namespace Jui
{
	// Button /////////////////////////////////////////////////////

	class Button : public Canvas
	{
		Q_OBJECT

	public:
		Button(QWidget *parent = 0);

		void label_(QString txt);
		void pressable_(bool b);
		void icon_(const char* img, int offset = 0);

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

	protected:
		void resizeEvent(QResizeEvent *e) override;
		void paintEvent(QPaintEvent *e) override;

	private:
		PureText *label, *current;
		LineText *target, *fadetime;
		FadeDouble variable;
		int cntDecNums;
		qint64 startTime;
		QPoint pt1;

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

	protected:
		void resizeEvent(QResizeEvent *e) override;

	private:
		PureText *label;
		LineText *txt;
		
		private slots:
		void onSet();
	};
}

#endif // BUTTON_H
