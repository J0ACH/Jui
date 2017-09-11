#ifndef CONFIG_H
#define CONFIG_H

#include "Canvas.h"
#include "Draw.h"
#include "Dummy.h"
#include "Button.h"

namespace Jui
{
	class Config : public Canvas
	{
		
	public:
		Config(int x, int y, int width, int height);
		~Config();

	public slots:
		void onPrint();
			
	};
}

#endif // CONFIG_H