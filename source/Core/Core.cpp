#include "Core.h"

namespace Jui
{
	FadeVariable::FadeVariable() {
		variable = new QVariantAnimation(this);
		connect(
			variable, SIGNAL(valueChanged(QVariant)),
			this, SLOT(onVariableChanged())
		);
	}
	void FadeVariable::value_(double value) {
		variable->setStartValue(value);
		variable->setEndValue(value);
	}
	void FadeVariable::value_(double value, double time) {
		//if (variable.state() == QAbstractAnimation::State::Running) { variable.stop(); }
		//variable.setStartValue(variable.currentValue());
		variable->setStartValue(variable->endValue());
		variable->setEndValue(value);
		variable->setDuration(time);
		variable->start();
	}
	double FadeVariable::value() { return variable->currentValue().value<double>(); }
	void FadeVariable::onVariableChanged() {
		qDebug() << tr("FadeVariable::value = %1").arg(
			QString::number(variable->currentValue().value<double>())
		);
	}

	void fadeVariant(QVariantAnimation &variable, Jui::fade fade, int duration) {
		/*
		connect(
		&variable, SIGNAL(valueChanged(QVariant)),
		this, SLOT(update())
		);
		*/

		if (variable.state() == QAbstractAnimation::State::Running) { variable.pause(); }
		variable.setDuration(duration);
		switch (fade)
		{
		case Jui::fade::in:
			variable.setDirection(QVariantAnimation::Direction::Forward);
			break;
		case Jui::fade::out:
			variable.setDirection(QVariantAnimation::Direction::Backward);
			break;
		}

		switch (variable.state())
		{
		case QAbstractAnimation::State::Paused:
			variable.resume();
			break;
		default:
			variable.start();
			break;
		}

	}
}