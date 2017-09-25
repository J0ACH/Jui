#include "Core.h"

namespace Jui
{
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