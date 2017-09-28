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
	void FadeFloat::value_(float value, float ftime) {
		this->stop();
		variable.setStartValue(this->value());
		variable.setEndValue(value);
		variable.setDuration(ftime * 1000);
		variable.start();
	}
	float FadeFloat::value() { return variable.currentValue().toFloat(); }

	// FadeInt /////////////////////////////////////////////////////

	void FadeInt::value_(int value) { FadeInt::value_(value, 0); }
	void FadeInt::value_(int value, float ftime) {
		this->stop();
		variable.setStartValue(this->value());
		variable.setEndValue(value);
		variable.setDuration(ftime * 1000);
		variable.start();
	}
	int FadeInt::value() { return variable.currentValue().toInt(); }

	// FadeColor /////////////////////////////////////////////////////


	FadeColor::FadeColor() : FadeAbstract() { FadeColor::value_(QColor(0, 0, 0, 0)); }
	void FadeColor::value_(QColor value) { FadeColor::value_(value, 0); }
	void FadeColor::value_(QColor value, float ftime) {
		this->stop();
		variable.setStartValue(this->value());
		variable.setEndValue(value);
		variable.setDuration(ftime * 1000);
		variable.start();
	}
	QColor FadeColor::value() { return variable.currentValue().value<QColor>(); }


}