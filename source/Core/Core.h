#ifndef CORE_H
#define CORE_H

#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QVariantAnimation>
#include <QMetaMethod>


namespace Jui
{
	enum fade { out, in };
	enum direction { right, bottom, left, top };

	void fadeVariant(QVariantAnimation &variable, Jui::fade fade, int duration);

	class FadeVariable : public QObject
	{
		Q_OBJECT

	public:
		FadeVariable();
		void value_(double value);
		void value_(double value, double time);
		double value();

		void reciever(QObject *object, const char* method);
				
	private:
		QObject *m_target;
		const char * m_method;
		QVariantAnimation variable;
		
		private slots :
			void onValueChanged();
	};
}

#endif // CORE_H