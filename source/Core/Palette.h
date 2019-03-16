#ifndef PALETTE_H
#define PALETTE_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

namespace Jui
{
		
	// Palette /////////////////////////////////////////////////////

	class Palette
	{

	public:
		Palette();

		enum colorTheme { dark, light };

		void palette_(QPalette palette);
		QPalette palette();

		void theme_(Palette::colorTheme theme);
		void color_(QColor color);


	private:
		QPalette m_palette;
		colorTheme m_theme;

		void initPalette(Palette::colorTheme theme);
		QColor getWindowsAccentColor();
	};
}

#endif // PALETTE_H