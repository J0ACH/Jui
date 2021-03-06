#include "Palette.h"

namespace Jui
{
	// Palette /////////////////////////////////////////////////////

	Palette::Palette()
	{
		m_theme = Palette::colorTheme::Dark;
		initPalette(m_theme);
	}


	void Palette::initPalette(Palette::colorTheme theme) {

		m_palette.setColor(QPalette::ColorGroup::Active, QPalette::ColorRole::Highlight, getWindowsAccentColor());
		//m_palette.setColor(QPalette::ColorRole::Button, QColor(150, 0, 0));

		switch (m_theme)
		{
		case Palette::colorTheme::Light:
			m_palette.setColor(QPalette::ColorGroup::All, QPalette::ColorRole::Window, QColor(255, 255, 255));

			m_palette.setColor(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, QColor(255, 255, 255));
			m_palette.setColor(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, QColor(255, 255, 255));
			m_palette.setColor(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, QColor(255, 255, 255));

			m_palette.setColor(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Highlight, QColor(240, 240, 240));

			m_palette.setColor(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, QColor(60, 60, 60));
			m_palette.setColor(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, QColor(60, 60, 60));
			m_palette.setColor(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, QColor(60, 60, 60));
			break;

		default:
			m_palette.setColor(QPalette::ColorGroup::All, QPalette::ColorRole::Window, QColor(30, 30, 30));

			m_palette.setColor(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, QColor(30, 30, 30));
			m_palette.setColor(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, QColor(30, 30, 30));
			m_palette.setColor(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, QColor(255, 255, 255));

			m_palette.setColor(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Highlight, QColor(40, 40, 40));

			m_palette.setColor(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, QColor(160, 160, 160));
			m_palette.setColor(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, QColor(160, 160, 160));
			m_palette.setColor(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, QColor(160, 160, 160));
			break;
		}
	}

	void Palette::palette_(QPalette palette) { m_palette = palette; }
	QPalette Palette::palette() { return m_palette; }

	void Palette::theme_(Palette::colorTheme theme) { initPalette(theme); }
	void Palette::color_(QColor color) {  }

	QColor Palette::getWindowsAccentColor() {
		QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\DWM", QSettings::NativeFormat);
		QVariant variant = settings.value("AccentColor");
		variant.convert(QVariant::UInt);
		uint intColor = variant.toInt();
		byte r = (byte)(intColor >> 0);
		byte g = (byte)(intColor >> 8);
		byte b = (byte)(intColor >> 16);
		byte a = (byte)(intColor >> 24);
		return QColor(r, g, b, a);
	}

}