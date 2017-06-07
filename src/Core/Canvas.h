#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>

namespace Jui
{
	class Canvas : public QWidget
	{
		Q_OBJECT

	public:
		Canvas(QWidget *parent, int x, int y, int width, int height);
		Canvas(int x, int y, int width, int height);
		~Canvas();

		void setName(QString name);
		void setBackgroundAlpha(int alpha);
		void setBackgroundColor(int red, int green, int blue);
		void setFrameAlpha(int alpha);
		void setFrameColor(int red, int green, int blue);

	public slots:
		void onClose();

	signals:
		//void actClosed(Canvan *obj);
		//void actMousePressed(Canvas *obj, int x, int y);
		void actMousePressed();
		//void actClosed();

	protected:
		void mousePressEvent(QMouseEvent *event);
		void paintEvent(QPaintEvent *event);

	private:
		void init(int x, int y, int width, int height);

		QString name;
		QColor colorBackround, colorFrame;
	};
}

#endif // CANVAS_H
