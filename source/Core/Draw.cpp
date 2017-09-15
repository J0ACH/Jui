#include "Draw.h"

namespace Jui
{
	Layer::Layer() {
		m_name = "NaN";
		m_alpha = 1;
	}
	Layer::Layer(QString name) : m_name(name) {
		m_alpha = 1;
	}

	void Layer::name_(QString name) { m_name = name; }
	QString Layer::name() { return m_name; }

	void Layer::alpha_(double a) { m_alpha = a; }
	double Layer::alpha() { return m_alpha; }

	void Layer::draw(QPainter &painter) { }

	Layer::~Layer() { qDebug("Layer closed"); }

}