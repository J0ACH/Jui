#include "Draw.h"

namespace Jui
{
	Layer::Layer() : m_name("NaN"), m_alpha(1) { }
	Layer::Layer(QString name) : m_name(name), m_alpha(1) { }

	void Layer::name_(QString name) { m_name = name; }
	QString Layer::name() { return m_name; }

	void Layer::alpha_(double a) { m_alpha = a; }
	double Layer::alpha() { return m_alpha; }
	void Layer::alphaFade(double value, int duration) {
		//connect(m_alphaClock, SIGNAL(timeout()), this, SLOT(alphaUpdate(value)));
		fps = 25;
		m_alphaClock->start(1000/fps);
	}
	void Layer::alphaUpdate(double target) {
		ratio += 1.0 / fps;
		if (ratio >= 1)
		{
			m_alphaClock->stop();
			ratio = 1;
		}
		//qDebug() << tr("Layer::alphaUpdate ratio: %1").arg(QString::number(ratio));
	}

	void Layer::draw(QPainter *painter, QRect bounds) { }

	Layer::~Layer() { qDebug("Layer closed"); }

	// Layer background /////////////////////////////////

	LayerBackground::LayerBackground() { this->name_("background"); }
	LayerBackground::LayerBackground(QString name) { }
	void LayerBackground::color_(QColor color) { colorBackground = color; }
	void LayerBackground::color_(int r, int g, int b, int a) { colorBackground = QColor(r, g, b, a); }
	void LayerBackground::draw(QPainter *painter, QRect bounds)
	{
		painter->fillRect(bounds, colorBackground);
	}

	// Layer frame /////////////////////////////////

	LayerFrame::LayerFrame() { this->name_("frame"); }
	LayerFrame::LayerFrame(QString name) { }
	void LayerFrame::color_(QColor color) { colorFrame = color; }
	void LayerFrame::color_(int r, int g, int b, int a) { colorFrame = QColor(r, g, b, a); }
	void LayerFrame::draw(QPainter *painter, QRect bounds)
	{
		painter->setPen(colorFrame);
		painter->drawRect(QRect(0, 0, bounds.width() - 1, bounds.height() - 1));
	}
}