#ifndef CORE_H
#define CORE_H

#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QVariant>
#include <QVariantAnimation>
#include <QMetaMethod>

namespace Jui
{
	enum fade { out, in };
	enum direction { right, bottom, left, top };

	void fadeVariant(QVariantAnimation &variable, Jui::fade fade, int duration);

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

#endif // CORE_H