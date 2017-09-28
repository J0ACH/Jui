#include "Fade.h"

namespace Jui
{
	// FadeFloat /////////////////////////////////////////////////////

	FadeFloat::FadeFloat() : QObject(0) { qDebug() << tr("FadeFloat::NEW()"); }
	void FadeFloat::value_(float value) { FadeFloat::value_(value, 0); }
	void FadeFloat::value_(float value, int ftime) {
		this->stop();
		variable.setStartValue(this->value());
		variable.setEndValue(value);
		variable.setDuration(ftime*1000);
		variable.start();
		/*
		qDebug() << tr("FadeVariable::value_ END (%1, t%2, %3, t%4, %5, d%6)").arg(
			QString::number(variable.startValue().value<double>()),
			QString::number(variable.startValue().type()),
			QString::number(variable.endValue().value<double>()),
			QString::number(variable.endValue().type()),
			QString::number(variable.duration()),
			QString::number(variable.state())
		);
		*/
	}
	float FadeFloat::value() { return variable.currentValue().toFloat(); }

	void FadeFloat::stop() {
		if (variable.state() == QAbstractAnimation::State::Running) { variable.stop(); }
	}
	void FadeFloat::reciever(QObject *object, const char * method) {
		m_target = object;
		m_method = method;
		connect(
			&variable, &QVariantAnimation::valueChanged,
			this, &FadeFloat::onValueChanged
		);
		//qDebug() << "FadeVariable::reciever set";
	}
	void FadeFloat::onValueChanged(QVariant val) {
		//qDebug() << tr("FadeVariable::onValueChanged(%1)").arg(val.toString());
		QMetaObject::invokeMethod(m_target, m_method);
	}

	// FadeInt /////////////////////////////////////////////////////

	FadeInt::FadeInt() : FadeFloat() { FadeFloat::value_(0); }
	void FadeInt::value_(int value) { FadeFloat::value_(value); }
	void FadeInt::value_(int value, int ftime) { FadeFloat::value_(value, ftime); }
	int FadeInt::value() { 
		/*
		int nint(double x) // provided by koahnig at qt-project.org
		{// avoids binary rounding error in (int) conversion
			return x < 0 ? (int)ceil(x) : (int)floor(x);
		}
		*/

		return (int) FadeFloat::value(); 
	}

	// FColor /////////////////////////////////////////////////////

	/*
	FColor::FColor() : FadeVariable() { FadeVariable::value_(QColor(0, 0, 0, 0)); }
	//FColor::FColor(QObject *parent) : FadeVariable(parent) { FadeVariable::value_(QColor(0, 0, 0, 0)); }
	void FColor::value_(QColor value) { FadeVariable::value_(value); }
	void FColor::value_(QColor value, double time) { FadeVariable::value_(value, time); }
	QColor FColor::value() { return FadeVariable::value().value<QColor>(); }
	*/

}