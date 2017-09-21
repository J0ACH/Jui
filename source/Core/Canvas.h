#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include "Draw.h"
#include "Core.h"

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

		void addLayer(Layer* layer);
		Layer* getLayer(QString name);

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

		//virtual void draw(QPainter &painter);
		//virtual void draw2(QPainter *painter);


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

		QHash<QString, Layer*> layers;
		QList<Layer*> order;
	};

	

	class Canvas2 : public QWidget
	{
	public:
		//enum fade { out, in };

		Canvas2(Canvas2 *parent = 0);
		Canvas2(Canvas2 *parent, int x, int y, int width, int height);
		Canvas2(int x, int y, int width, int height);

		void origin_(int x, int y);
		QPoint origin();

	protected:
		void moveEvent(QMoveEvent *event) override;
		void paintEvent(QPaintEvent *e) override;
		
	private:
		void init(int x = 10, int y = 10, int width = 50, int height = 50);
	};
}

#endif // CANVAS_H
