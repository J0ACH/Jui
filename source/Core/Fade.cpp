#include "Fade.h"

namespace Jui
{
	// FadeAbstract /////////////////////////////////////////////////////

	FadeAbstract::FadeAbstract() : QObject(0) {	}
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
	}
	void FadeAbstract::updater(QWidget *widget) {
		QObject::connect(
			&variable, SIGNAL(valueChanged()),
			widget, SLOT(update())
		);
	}
	void FadeAbstract::onValueChanged(QVariant val) {
		QMetaObject::invokeMethod(m_target, m_method);
	}

	// FadeDouble /////////////////////////////////////////////////////

	void FadeDouble::value_(double value) { FadeDouble::value_(value, 0); }
	void FadeDouble::value_(double value, double ftime) {
		this->stop();
		variable.setStartValue(this->value());
		variable.setEndValue(value);
		variable.setDuration(ftime * 1000);
		variable.start();
	}
	double FadeDouble::value() { return variable.currentValue().toDouble(); }

	// FadeInt /////////////////////////////////////////////////////

	void FadeInt::value_(int value) { FadeInt::value_(value, 0); }
	void FadeInt::value_(int value, double ftime) {
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
	void FadeColor::value_(int r, int g, int b) { FadeColor::value_(QColor(r, g, b), 0); }
	void FadeColor::value_(int r, int g, int b, double ftime) { FadeColor::value_(QColor(r, g, b), ftime); }
	void FadeColor::value_(QColor value, double ftime) {
		this->stop();
		variable.setStartValue(this->value());
		variable.setEndValue(value);
		variable.setDuration(ftime * 1000);
		variable.start();
	}
	QColor FadeColor::value() { return variable.currentValue().value<QColor>(); }

	// FadePoint /////////////////////////////////////////////////////

	void FadePoint::value_(QPoint value) { FadePoint::value_(value, 0); }
	void FadePoint::value_(QPoint value, double ftime) {
		this->stop();
		variable.setStartValue(this->value());
		variable.setEndValue(value);
		variable.setDuration(ftime * 1000);
		variable.start();
	}
	void FadePoint::value_(int x, int y, double ftime) { FadePoint::value_(QPoint(x, y), ftime); }
	QPoint FadePoint::value() { return variable.currentValue().toPoint(); }

}