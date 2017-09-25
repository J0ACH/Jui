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

		//void target(QObject *object, QString method);
		void target(QObject *object, const char* method);
		//void target(QObject *object, QMetaMethod method);
		//void target(QObject *object, std::function<bool(int)>);
		//void target(QObject *object, void *method);

		double value();

		public slots:
		void onVariableChanged();

	private:
		QObject *m_target;
		const char * m_method;
		//QString m_method;
		QVariantAnimation variable;
		
		private slots :
			void onValueChanged();
	};
}

#endif // CORE_H