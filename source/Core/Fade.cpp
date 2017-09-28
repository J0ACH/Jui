#include "Fade.h"

namespace Jui
{
	// FadeAbstract /////////////////////////////////////////////////////

	FadeAbstract::FadeAbstract() : QObject(0) {
		qDebug() << tr("FadeAbstract::NEW()");
	}
	void FadeAbstract::stop() {
		if (variable.state() == QAbstractAnimation::State::Running) { variable.stop(); }
	}
	void FadeAbstract::reciever(QObject *object, const char * method) {
		m_target = object;
		m_method = method;
		connect(
			&variable, &QVariantAnimation::valueChanged,
			this, &FadeAbstract::onValueChanged
		);
		//qDebug() << "FadeVariable::reciever set";
	}
	void FadeAbstract::onValueChanged(QVariant val) {
		//qDebug() << tr("FadeVariable::onValueChanged(%1)").arg(val.toString());
		QMetaObject::invokeMethod(m_target, m_method);
	}

	// FadeFloat /////////////////////////////////////////////////////

	void FadeFloat::value_(float value) { FadeFloat::value_(value, 0); }
	void FadeFloat::value_(float value, int ftime) {
		this->stop();
		variable.setStartValue(this->value());
		variable.setEndValue(value);
		variable.setDuration(ftime * 1000);
		variable.start();
	}
	float FadeFloat::value() { return variable.currentValue().toFloat(); }

	// FadeInt /////////////////////////////////////////////////////

	void FadeInt::value_(int value) { FadeInt::value_(value, 0); }
	void FadeInt::value_(int value, int ftime) {
		this->stop();
		variable.setStartValue(this->value());
		variable.setEndValue(value);
		variable.setDuration(ftime * 1000);
		variable.start();
	}
	int FadeInt::value() { return variable.currentValue().toInt(); }

	// FColor /////////////////////////////////////////////////////

	/*
	FColor::FColor() : FadeVariable() { FadeVariable::value_(QColor(0, 0, 0, 0)); }
	void FColor::value_(QColor value) { FadeVariable::value_(value); }
	void FColor::value_(QColor value, double time) { FadeVariable::value_(value, time); }
	QColor FColor::value() { return FadeVariable::value().value<QColor>(); }
	*/

}