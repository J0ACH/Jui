#ifndef BUTTON_H
#define BUTTON_H

#include "Canvas.h"
#include <QPushButton>
#include <QPropertyAnimation>

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
		Q_OBJECT
		
	public :
		Button2(QWidget *parent = 0);

		void colorFrame_(QColor normal, QColor over);
		QColor colorFrame();
		void colorBackground_(QColor off, QColor on);
		QColor colorBackground();


	protected:
		void enterEvent(QEvent *e) override;
		void leaveEvent(QEvent *e) override;
		void mousePressEvent(QMouseEvent *e) override;
		void mouseReleaseEvent(QMouseEvent *e) override;
		void paintEvent(QPaintEvent *e) override;
		
		virtual void draw_OffOut(QPainter* painter);
		virtual void draw_OffOver(QPainter* painter);
		virtual void draw_Press(QPainter* painter);
		virtual void draw_OnOut(QPainter* painter);
		virtual void draw_OnOver(QPainter* painter);
		
	private:
		enum state {offOut, offOver, press, onOut, onOver};
		state m_state, prev_state;

				
		QVariantAnimation fade_colorFrame, fade_colorBackground;
		
		enum fade { out, in };
		void fadeVariant(QVariantAnimation &var, Button2::fade fade, int duration);
	};


}

#endif // BUTTON_H