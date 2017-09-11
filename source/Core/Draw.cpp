#include "Draw.h"

namespace Jui
{
	Layer::Layer(Canvas *parent) :
		QWidget(parent),
		//mPainter(new QPainter(this)),
		mAlpha(0)
	{
		
	}

	void Layer::alpha_(double a) { mAlpha = a; }
	double Layer::alpha() { return mAlpha; }

	double Layer::alpha2(Layer* l) {
		qDebug() << tr("Layer a:%1").arg(
			QString::number(l->alpha())
		);
		return l->alpha();
	}

	Layer::~Layer()
	{
		qDebug("Layer closed");
	}

}