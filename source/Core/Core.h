#ifndef CORE_H
#define CORE_H

#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QVariantAnimation>

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
		
		public slots:
		void onVariableChanged();

	private:
		QVariantAnimation *variable;
	};
}

#endif // CORE_H