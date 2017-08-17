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

		enum type { Window, Panel };
		
		Canvas *getParent();
		QPoint getOrigin(bool global = false);
		QString getName();
		Canvas::type getType();
				
		void setName(QString name);
		void setBackgroundAlpha(int alpha);
		void setBackgroundColor(int red, int green, int blue);
		void setFrameAlpha(int alpha);
		void setFrameColor(int red, int green, int blue);

		public slots:
		void onClose();
		void onMove(QPoint);
		void onResize(QSize);

	signals:
		void actClosed(Canvas *target);
		void actOverIn(Canvas *target);
		void actOverOut(Canvas *target);
		void actFocusIn(Canvas *target);
		void actFocusOut(Canvas *target);
		void actMousePressed(Canvas *target, QPoint gPt);
		void actMouseMoved(Canvas *target, QPoint gPt);
		void actMouseReleased(Canvas *target, QPoint gPt);

	protected:
		void focusInEvent(QFocusEvent *event);
		void focusOutEvent(QFocusEvent *event);

		void enterEvent(QEvent *event);
		void leaveEvent(QEvent *event);

		void mousePressEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);

		void paintEvent(QPaintEvent *event);

	private:
		void init(int x, int y, int width, int height);

		Canvas *mParent;
		Canvas::type mType;

		QString name;
		QPoint origin;

		QColor colorBackround, colorFrame;

	};


}

#endif // CANVAS_H