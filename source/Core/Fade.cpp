#include "Fade.h"

namespace Jui
{
	// FadeVariable /////////////////////////////////////////////////////

	FadeVariable::FadeVariable() { this->value_(0); }
	void FadeVariable::value_(QVariant value) {
		variable.setStartValue(value);
		variable.setEndValue(value);
	}
	void FadeVariable::value_(QVariant value, double time) {
		this->stop();
		variable.setStartValue(this->value());
		variable.setEndValue(value);
		variable.setDuration(time);
		variable.start();
	}
	QVariant FadeVariable::value() { return variable.currentValue(); }
	void FadeVariable::stop() {
		if (variable.state() == QAbstractAnimation::State::Running) { variable.stop(); }
	}
	void FadeVariable::reciever(QObject *object, const char * method) {
		m_target = object;
		m_method = method;
		connect(
			&variable, SIGNAL(valueChanged(QVariant)),
			this, SLOT(onValueChanged())
		);
	}
	void FadeVariable::onValueChanged() {
		QMetaObject::invokeMethod(m_target, m_method);
	}

	// fDouble /////////////////////////////////////////////////////

	fDouble::fDouble() { this->value_(0); }
	void fDouble::value_(double value) { FadeVariable::value_(value); }
	void fDouble::value_(double value, double time) { FadeVariable::value_(value, time); }
	double fDouble::value() { return FadeVariable::value().value<double>(); }

}