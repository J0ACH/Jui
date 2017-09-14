#include "Draw.h"

namespace Jui
{
	Layer::Layer(QWidget *parent, QString name) :
		QWidget(parent),
		m_name(name),
		mAlpha(0)
	{

	}

	QString Layer::name() { return m_name; }

	void Layer::alpha_(double a) { mAlpha = a; }
	double Layer::alpha() { return mAlpha; }
/*
	double Layer::alpha2(Layer* l) {
		qDebug() << tr("Layer a:%1").arg(
			QString::number(l->alpha())
		);
		return l->alpha();
	}
*/

	void Layer::draw(QPainter &painter) {
		painter.setPen(QColor(30, 230, 30));
		painter.drawLine(0, 0, 30, 30);
	}

	Layer::~Layer()
	{
		qDebug("Layer closed");
	}

}