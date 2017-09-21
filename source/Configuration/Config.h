#ifndef CONFIG_H
#define CONFIG_H

#include "Canvas.h"
#include "Draw.h"
#include "Dummy.h"
#include "Button.h"


namespace Jui
{
	class Config : public Canvas2
	{		
	public:
		Config(int x, int y, int width, int height);	
	};
}

#endif // CONFIG_H