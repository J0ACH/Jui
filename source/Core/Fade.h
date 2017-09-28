#ifndef FADE_H
#define FADE_H

#include <QObject>
#include <QDebug>
#include <QMetaObject>
#include <QVariantAnimation>
#include <QColor>

namespace Jui
{
	class FadeFloat : public QObject
	{
		Q_OBJECT

	public:
		FadeFloat();
		void value_(float value);
		void value_(float value, int ftime);
		float value();
		void stop();

		void reciever(QObject *object, const char* method);

	protected:
		QObject *m_target;
		const char *m_method;
		
	private:
		QVariantAnimation variable;
		void onValueChanged(QVariant);
	};

	// FDouble /////////////////////////////////////////////////////

	class FadeInt : public FadeFloat
	{
	public:
		FadeInt();
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
		//FColor(QObject * parent);
		void value_(QColor value);
		void value_(QColor value, double time);
		QColor value();
	};
	*/

}

#endif // FADE_H