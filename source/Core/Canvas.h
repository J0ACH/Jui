#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include "Draw.h"
#include "Core.h"

namespace Jui
{
	class Canvas : public QWidget
	{
		
	public:
		Canvas(QWidget *parent = 0);
		Canvas(QWidget *parent, int x, int y, int width, int height);
		Canvas(int x, int y, int width, int height);

		void origin_(int x, int y);
		QPoint origin();

	protected:
		void paintEvent(QPaintEvent *e) override;
				
	private:
		void init(int x = 10, int y = 10, int width = 50, int height = 50);
	};
}

#endif // CANVAS_H
