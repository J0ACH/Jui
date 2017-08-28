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

	signals:
		void actPressed(Button*);

		public slots:
		void onPress();
		void draw();

	private:
		enum stateSwitch {on, off};
		Button::stateSwitch mSwitch;
		
		void init();
	};

}

#endif // BUTTON_H