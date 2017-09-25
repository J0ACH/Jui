#include "Core.h"

namespace Jui
{
	FadeVariable::FadeVariable() :
		m_target(this),
		m_method("onVariableChanged")
	{
		connect(
			&variable, SIGNAL(valueChanged(QVariant)),
			this, SLOT(onValueChanged())
		);
	}
	void FadeVariable::value_(double value) {
		variable.setStartValue(value);
		variable.setEndValue(value);
	}
	void FadeVariable::value_(double value, double time) {
		if (variable.state() == QAbstractAnimation::State::Running) { variable.stop(); }
		variable.setStartValue(variable.currentValue());
		variable.setEndValue(value);
		variable.setDuration(time);
		variable.start();
	}
	double FadeVariable::value() { return variable.currentValue().value<double>(); }
	void FadeVariable::target(QObject *object, const char * method)
	{
		//m_target = object->metaObject();
		m_target = object;
		m_method = method;
		qDebug() << tr("FadeVariable::target qstring [%1 || %2]").arg(
			object->metaObject()->className(),
			method
		);
	}
	void FadeVariable::onValueChanged() {
		QMetaObject::invokeMethod(m_target, m_method);
	}
	void FadeVariable::onVariableChanged() {
		qDebug() << tr("FadeVariable::value = %1").arg(
			QString::number(value())
		);
	}
	/*
	void FadeVariable::target2(void (*method)())
	{
		qDebug() << tr("FadeVariable::target qstring [%1]").arg(
			"method"
		);
	}
	*/
	/*
	void FadeVariable::target(QObject *object, std::function<bool(int)>)
	{
		qDebug() << tr("FadeVariable::target [%1 || %2]").arg(
			object->objectName(), "method"
		);

		connect(
			&variable, SIGNAL(valueChanged(QVariant)),
			object, SLOT(update())
		);
	}
	*/

	/*
	void FadeVariable::target(QObject *object, void *method)
	{
		qDebug() << tr("FadeVariable::target void [%1 || %2]").arg(
			object->metaObject()->className(),
			"method2"
		);
	}
	void FadeVariable::target(QObject *object, const char* method)
	{
		const QMetaObject *mObj = object->metaObject();
		int methodIndex = object->metaObject()->indexOfMethod(method);
		QMetaMethod mMethod = object->metaObject()->method(methodIndex);

		qDebug() << tr("FadeVariable::target qstring [%1 || %2]").arg(
			mObj->className(), mMethod.tag()
		);

		connect(
			&variable, SIGNAL(valueChanged(QVariant)),
			object, SLOT()
		);

	}
	*/



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