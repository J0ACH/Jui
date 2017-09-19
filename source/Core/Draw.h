#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QMessageLogger>

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

		void alpha_(double value);
		double alpha();
		void alphaFade(double value, int duration);

		virtual void draw(QPainter *painter, QRect bounds);

	protected:
		QString m_name;
		double m_alpha;

	private:
		QTimer *m_alphaClock;
		int fps;
		double ratio;

		//private slots:
		void alphaUpdate(double target);
	};

	// Layer background /////////////////////////////////

	class LayerBackground : public Layer
	{
	public:
		LayerBackground();
		LayerBackground(QString name);
		void color_(QColor color);
		void color_(int r, int g, int b, int a = 255);
		void draw(QPainter *painter, QRect bounds) override;
	private:
		QColor colorBackground;
	};

	// Layer frame /////////////////////////////////

	class LayerFrame : public Layer
	{
	public:
		LayerFrame();
		LayerFrame(QString name);
		void color_(QColor color);
		void color_(int r, int g, int b, int a = 255);
		void draw(QPainter *painter, QRect bounds) override;
	private:
		QColor colorFrame;
	};

}

#endif // DRAW_H