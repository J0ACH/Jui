#ifndef BUTTON_H
#define BUTTON_H

#include "Canvas.h"
#include <QPushButton>
//#include <QVariantAnimation>

namespace Jui
{
	class Button : public Canvas
	{
		Q_OBJECT

	public:
		Button(Canvas *parent);
		Button(Canvas *parent, int x, int y, int width, int height);
		~Button();

		void addState(QString name);

		int getState();
		QString getStateName();

		void setStateCounter(int cnt);

	signals:
		void actPressed(Button*);

		public slots:
		//virtual void changed();

	protected:


	private:
		void init();

		int intCounter, maxCounter;
		QList<QString> stateNames;

		private slots:
		void prOnPressed();


	};

	class Button2 : public QPushButton
	{

	public:
		Button2(QWidget *parent = 0);
		
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
		//enum fade { out, in };
		//void fadeVariant(QVariantAnimation &var, Button2::fade fade, int duration);
		QVariantAnimation fade_colorFrame, fade_colorBackground;
	};

	class Button3 : private Canvas2
	{
	public:
		Button3(Canvas2 *parent, int x, int y, int width, int height);

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
		QPushButton *m_button;
		QVariantAnimation fade_colorFrame, fade_colorBackground;
	};

}

#endif // BUTTON_H