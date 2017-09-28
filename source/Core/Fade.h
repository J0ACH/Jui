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
		void reciever(QObject *object, const char* method = "update");

	protected:
		QVariantAnimation variable;
		QObject *m_target;
		const char *m_method;
	private:
		void onValueChanged(QVariant);
	};

	// FadeInt /////////////////////////////////////////////////////

	class FadeFloat : public FadeAbstract
	{
	public:
		void value_(float value);
		void value_(float value, float ftime);
		float value();
	};

	// FadeInt /////////////////////////////////////////////////////

	class FadeInt : public FadeAbstract
	{
	public:
		void value_(int value);
		void value_(int value, float ftime);
		int value();
	};

	// FadeColor /////////////////////////////////////////////////////

	class FadeColor : public FadeAbstract
	{
	public:
		FadeColor();
		void value_(QColor value);
		void value_(int r, int g, int b);
		void value_(int r, int g, int b, float ftime);
		void value_(QColor value, float time);
		QColor value();
	};


}

#endif // FADE_H