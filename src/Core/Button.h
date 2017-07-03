#ifndef BUTTON_H
#define BUTTON_H

#include "Canvas.h"

namespace Jui
{
	class Button : public Canvas
	{

	public:
		Button(Canvas *parent, int x, int y, int width, int height);
		~Button();

	protected:
		void paintEvent(QPaintEvent *event);
		
	private:
		QString name;
		QColor colorOver;
	};

}

#endif // BUTTON_H