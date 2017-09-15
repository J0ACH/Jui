#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <QPainter>
#include <QDebug>

namespace Jui
{
	class Layer
	{
	public:
		Layer();
		Layer(QString name);
		~Layer();

		void name_(QString name);
		QString name();

		void alpha_(double);
		double alpha();

		virtual void draw(QPainter *painter, QRect bounds);

	protected:
		QString m_name;
		double m_alpha;
	};

	class LayerBackground : public Layer
	{
	public:
		LayerBackground();
		LayerBackground(QString name);		
		void background_(QColor color);
		void background_(int r, int g, int b, int a = 255);
		void draw(QPainter *painter, QRect bounds) override;
	private:
		QColor m_background;
	};


}

#endif // DRAW_H