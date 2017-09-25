#ifndef FADE_H
#define FADE_H

#include <QDebug>
#include <QMetaObject>
#include <QVariantAnimation>
#include <QVariant>
#include <QColor>

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

	// FDouble /////////////////////////////////////////////////////

	class FDouble : public FadeVariable
	{
	public:
		FDouble();
		void value_(double value);
		void value_(double value, double time);
		double value();
	};
	
	// FColor /////////////////////////////////////////////////////
	
	class FColor : public FadeVariable
	{
	public:
		FColor();
		void value_(QColor value);
		void value_(QColor value, double time);
		QColor value();
	};
	
}

#endif // FADE_H