#ifndef FADE_H
#define FADE_H

#include "Core.h"

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
		void updater(QWidget *widget);

	signals:
		void started();
		void changed();
		void finished();
		
	protected:
		QVariantAnimation variable;
		QObject *m_target;
		const char *m_method;
	private:
		void onValueChanged(QVariant);
		void onFinish();
	};

	// FadeDouble /////////////////////////////////////////////////////

	class FadeDouble : public FadeAbstract
	{
	public:
		void value_(double value);
		void value_(double value, double ftime);
		double value();		
		operator double() const;
	};

	// FadeInt /////////////////////////////////////////////////////

	class FadeInt : public FadeAbstract
	{
	public:
		void value_(int value);
		void value_(int value, double ftime);
		int value();
	};

	// FadeColor /////////////////////////////////////////////////////

	class FadeColor : public FadeAbstract
	{
	public:
		FadeColor();
		void value_(QColor value);
		void value_(int r, int g, int b);
		void value_(int r, int g, int b, double ftime);
		void value_(QColor value, double time);
		QColor value();
		operator QColor() const;
	};

	// FadePoint /////////////////////////////////////////////////////

	class FadePoint : public FadeAbstract
	{
	public:
		void value_(QPoint value);
		void value_(QPoint value, double ftime);
		void value_(int x, int y, double ftime);
		QPoint value();
	};



}

#endif // FADE_H