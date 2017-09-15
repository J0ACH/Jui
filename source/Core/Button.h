#ifndef BUTTON_H
#define BUTTON_H

#include "Canvas.h"
#include <QPushButton>


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
		//void draw(QPainter &painter) override;		

	private:
		void init();

		int intCounter, maxCounter;
		QList<QString> stateNames;
		
		private slots:
		void prOnPressed();


	};

	class Button2 : public QPushButton
	{
	public :
		Button2(QWidget *parent = 0);

	protected:
		void enterEvent(QEvent *event) override;
		void leaveEvent(QEvent *event) override;
		void mousePressEvent(QMouseEvent *event) override;
		void mouseReleaseEvent(QMouseEvent *event) override;
		void paintEvent(QPaintEvent *e) override;

		virtual void draw_OffOut(QPainter* painter);
		virtual void draw_OffOver(QPainter* painter);
		virtual void draw_Press(QPainter* painter);
		virtual void draw_OnOut(QPainter* painter);
		virtual void draw_OnOver(QPainter* painter);

	private:
		enum state {offOut, offOver, press, onOut, onOver};
		state m_state, prev_state;
		
	};

}

#endif // BUTTON_H