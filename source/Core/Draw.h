#ifndef DRAW_H
#define DRAW_H

//#include <QWidget>
//#include <QPainter>
#include "Canvas.h"

namespace Jui
{
	class Layer : public QWidget
	{
		Q_OBJECT

	public:
		Layer(Canvas *parent = 0);
		~Layer();

		void alpha_(double);
		double alpha();
		static double alpha2(Layer*);
		//double alpha2(Layer*);

		static void drawTest(Layer*);

	protected:
		//void paintEvent(QPaintEvent *event) override;

	private:
		//QPainter *mPainter;
		double mAlpha;

	};
}

#endif // DRAW_H