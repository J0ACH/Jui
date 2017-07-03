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
		Canvas(Canvas *parent = 0);
		Canvas(Canvas *parent, int x, int y, int width, int height);
		Canvas(int x, int y, int width, int height);
		~Canvas();

		void setName(QString name);
		QString getName();
		

		void setBackgroundAlpha(int alpha);
		void setBackgroundColor(int red, int green, int blue);
		void setFrameAlpha(int alpha);
		void setFrameColor(int red, int green, int blue);

		void connect2(QString signal, Canvas *target, QString slot);

		public slots:
		void onClose();

	signals:
		void actClosed(Canvas *target);
		void actMousePressed(Canvas *target, int x, int y);
		void actMouseReleased(Canvas *target, int x, int y);
		void actMouseEntered(Canvas *target);
		void actMouseLeaved(Canvas *target);
		
	protected:
		void focusInEvent(QFocusEvent *event);
		void focusOutEvent(QFocusEvent *event);

		void enterEvent(QEvent *event);
		void leaveEvent(QEvent *event);

		void mousePressEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);
		void paintEvent(QPaintEvent *event);

	private:
		void init(int x, int y, int width, int height);

		QString name;
		QColor colorBackround, colorFrame;
	};
}

#endif // CANVAS_H
