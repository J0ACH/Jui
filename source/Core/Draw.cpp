#include "Draw.h"

namespace Jui
{
	Layer::Layer() : m_name("NaN"), m_alpha(1) { }
	Layer::Layer(QString name) : m_name(name), m_alpha(1) { }

	void Layer::name_(QString name) { m_name = name; }
	QString Layer::name() { return m_name; }

	void Layer::alpha_(double a) { m_alpha = a; }
	double Layer::alpha() { return m_alpha; }

	void Layer::draw(QPainter *painter, QRect bounds) { }

	Layer::~Layer() { qDebug("Layer closed"); }

	// Layer background /////////////////////////////////

	LayerBackground::LayerBackground() { this->name_("background"); }
	LayerBackground::LayerBackground(QString name) { }
	void LayerBackground::background_(QColor color) { m_background = color; }
	void LayerBackground::background_(int r, int g, int b, int a) { 
		m_background = QColor(r, g, b, a);
	}
	void LayerBackground::draw(QPainter *painter, QRect bounds)
	{
		painter->fillRect(bounds, m_background);
	}
}