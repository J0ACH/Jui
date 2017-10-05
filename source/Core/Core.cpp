#include "Core.h"

namespace Jui
{
	void Jui::loadFonts() {
		int f1 = QFontDatabase::addApplicationFont(":/fontText.ttf");
		int f2 = QFontDatabase::addApplicationFont(":/fontConsole.ttf");
	};

}