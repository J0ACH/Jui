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

		enum states { normal, over, active, frozen };

		Canvas *getParent();
		QPoint getOrigin();
		QString getName();
		Canvas::states getState();

		QRect bounds();

		void setName(QString name);

		void setBackgroundVisible(bool);
		void setBackgroundAlpha(int alpha);
		void setBackgroundColor(int red, int green, int blue);

		void setFrameVisible(bool);
		void setFrameAlpha(int alpha);
		void setFrameColor(int red, int green, int blue);

		//virtual void parentResized(QSize);
		//virtual void draw(QPainter &painter);
		//virtual void draw2(QPainter *painter);

		public slots:
		void onClose();
		void setSize(QSize);
		void setOrigin(QPoint);

		virtual void changed();


	signals:
		void actClosed(Canvas *target);
		void actOverIn(Canvas *target);
		void actOverOut(Canvas *target);
		void actFocusIn(Canvas *target);
		void actFocusOut(Canvas *target);
		void actMousePressed(Canvas *target, QPoint gPt);
		void actMouseMoved(Canvas *target, QPoint gPt);
		void actMouseReleased(Canvas *target, QPoint gPt);
		void actResized(Canvas *target, QSize size);
		void actMoved(Canvas *target, QPoint gPt);

	protected:
		void focusInEvent(QFocusEvent *event) override;
		void focusOutEvent(QFocusEvent *event) override;

		void enterEvent(QEvent *event) override;
		void leaveEvent(QEvent *event) override;

		void mousePressEvent(QMouseEvent *event) override;
		void mouseReleaseEvent(QMouseEvent *event) override;
		void mouseMoveEvent(QMouseEvent *event) override;

		void moveEvent(QMoveEvent *event) override;
		void resizeEvent(QResizeEvent *event) override;
		void paintEvent(QPaintEvent *event) override;

		virtual void draw(QPainter &painter);


	private:
		enum type { Window, Panel };

		void init(int x, int y, int width, int height);

		Canvas *mParent;
		Canvas::type mType;
		Canvas::states mState;

		QString mName;
		QPoint origin;

		bool visibleFrame, visibleBackground;

		QColor colorBackround, colorFrame;
	};
}

#endif // CANVAS_H
