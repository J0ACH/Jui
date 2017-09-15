#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <QPainter>
#include <QDebug>

namespace Jui
{
	class Layer
	{
		//Q_OBJECT

	public:
		Layer();
		Layer(QString name);
		~Layer();

		void name_(QString name);
		QString name();

		void alpha_(double);
		double alpha();

		virtual void draw(QPainter &painter);

	private:
		QString m_name;
		double m_alpha;

	};


}

#endif // DRAW_H