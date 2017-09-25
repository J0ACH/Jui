#ifndef FADE_H
#define FADE_H

#include <QDebug>
#include <QVariant>
#include <QVariantAnimation>
#include <QMetaObject>

namespace Jui
{
	class FadeVariable : private QObject
	{
		Q_OBJECT

	public:
		FadeVariable();
		void value_(QVariant value);
		void value_(QVariant value, double time);
		QVariant value();
		void stop();

		void reciever(QObject *object, const char* method);

	protected:
		QVariantAnimation variable;
		QObject *m_target;
		const char * m_method;

	private slots :
		void onValueChanged();
	};

	// fDouble /////////////////////////////////////////////////////

	class fDouble : public FadeVariable
	{
	public:
		fDouble();
		void value_(double value);
		void value_(double value, double time);
		double value();
	};
	
	// fColor /////////////////////////////////////////////////////

	/*
	class fColor : public FadeVariable
	{
	};
	*/
}

#endif // FADE_H