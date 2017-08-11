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

		enum type { Windows, Panel };

		void setName(QString name);
		QString getName();

		Canvas *getParent();
		bool isWin();

		void setBackgroundAlpha(int alpha);
		void setBackgroundColor(int red, int green, int blue);
		void setFrameAlpha(int alpha);
		void setFrameColor(int red, int green, int blue);

		void connect2(QString signal, Canvas *target, QString slot);

		public slots:
		void onMousePress(QPoint);
		void onMove(QPoint);
		void onClose();

	signals:
		void actClosed(Canvas *target);
		void actMousePressed(QPoint globalPt, QPoint localPt);
		void actMouseMoved(QPoint globalPt, QPoint localPt);
		void actMouseReleased(Canvas *target, int x, int y);
		void actOverIn(Canvas *target);
		void actOverOut(Canvas *target);
		void actFocusIn(Canvas *target);
		void actFocusOut(Canvas *target);

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
		QColor colorBackround, colorFrame;

	};


}

#endif // CANVAS_H
