#ifndef BUTTON_H
#define BUTTON_H

#include "Canvas.h"

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
		virtual void changed();

	protected:
		//void paintEvent(QPaintEvent *event);
		void draw(QPainter &painter) override;
		

	private:
		void init();

		int intCounter, maxCounter;
		QList<QString> stateNames;
		
		private slots:
		void prOnPressed();


	};

}

#endif // BUTTON_H