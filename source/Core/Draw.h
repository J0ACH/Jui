#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <QPainter>
//#include "Canvas.h"

namespace Jui
{
	class Layer : public QWidget
	{
		Q_OBJECT

	public:
		Layer(QWidget *parent, QString name);
		~Layer();

		QString name();

		void alpha_(double);
		double alpha();


		//static double alpha2(Layer*);
		//double alpha2(Layer*);

		//static void drawTest(Layer*);
		virtual void draw(QPainter &painter);

	protected:
		//void paintEvent(QPaintEvent *event) override;

	private:
		//QPainter *mPainter;
		QString m_name;
		double mAlpha;

	};
}

#endif // DRAW_H