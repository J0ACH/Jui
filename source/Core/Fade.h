#ifndef FADE_H
#define FADE_H

#include <QObject>
#include <QDebug>
#include <QMetaObject>
#include <QVariantAnimation>
#include <QColor>

namespace Jui
{
	// FadeAbstract /////////////////////////////////////////////////////

	class FadeAbstract : public QObject
	{
		Q_OBJECT

	public:
		FadeAbstract();
		void stop();
		void reciever(QObject *object, const char* method);

	protected:
		QVariantAnimation variable;
		QObject *m_target;
		const char *m_method;
		void onValueChanged(QVariant);
	};

	// FadeInt /////////////////////////////////////////////////////

	class FadeFloat : public FadeAbstract
	{
	public:
		void value_(float value);
		void value_(float value, int ftime);
		float value();
	};

	// FadeInt /////////////////////////////////////////////////////

	class FadeInt : public FadeAbstract
	{
	public:
		void value_(int value);
		void value_(int value, int ftime);
		int value();
	};

	// FColor /////////////////////////////////////////////////////
	/*
	class FColor : public FadeVariable
	{
		Q_OBJECT

	public:
		FColor();
		void value_(QColor value);
		void value_(QColor value, double time);
		QColor value();
	};
	*/

}

#endif // FADE_H