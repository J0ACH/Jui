#ifndef DUMMY_H
#define DUMMY_H

#include "Canvas.h"
#include "Button.h"

namespace Jui
{
	// Header2 /////////////////////////////////////////////////////

	class Header2 : public Button
	{
	public:
		Header2(QWidget *parent);
	protected:
		void mousePressEvent(QMouseEvent *e) override;
		void mouseMoveEvent(QMouseEvent *e) override;
		void paintEvent(QPaintEvent *e) override;
	private:
		void fitGeometry();
		int thickness;
		QPoint mousePressedGlobalCoor, mousePressedOriginCoor;
		
	};

	// Header /////////////////////////////////////////////////////

	class Header : public Canvas
	{
		Q_OBJECT

	public:
		Header(Canvas *parent);
		~Header();

		//void parentResized(QSize);

	signals:
		void actHeaderMoved(QPoint);

		public slots:
		void onMousePress(Canvas*, QPoint);
		void onMouseMoved(Canvas*, QPoint);
		void onParentResize(Canvas*, QSize);

	protected:
		void paintEvent(QPaintEvent *event) override;

	private:
		int thickness;
		QPoint mousePressedGlobalCoor, mousePressedOriginCoor;
	};

	// HeaderDialog /////////////////////////////////////////////////////

	class HeaderDialog : public Header
	{
		Q_OBJECT

	public:
		HeaderDialog(Canvas *parent);
		~HeaderDialog();

		public slots:
		void onParentResize(Canvas*, QSize);

	private:
		Button* buttonClose;
	};

	// HeaderWindow /////////////////////////////////////////////////////

	class HeaderWindow : public Header
	{
		Q_OBJECT

	public:
		HeaderWindow(Canvas *parent);
		~HeaderWindow();

		public slots:
		void onParentResize(Canvas*, QSize);

	private:
		Button *buttonClose, *buttonMaximize, *buttonMinimize;
	};

	// EdgeControler ///////////////////////////////////////////////////// 

	class EdgeControler : public Canvas
	{
		Q_OBJECT

	public:
		enum direction { Right, Bottom, Left, Top };

		EdgeControler(Canvas* parent, EdgeControler::direction dir);
		~EdgeControler();

		EdgeControler::direction getDirection();

	signals:
		void actControlerMoved(EdgeControler::direction, QPoint deltaPt);

		public slots:
		void onMousePress(Canvas*, QPoint);
		void onMouseMoved(Canvas*, QPoint);

	protected:
		void paintEvent(QPaintEvent *event) override;

	private:
		EdgeControler::direction mDirection;
		QPoint mousePressedGlobalCoor;

	};

	// Edges ///////////////////////////////////////////////////// 

	class Edges : public QObject
	{
		Q_OBJECT

	public:
		Edges(Canvas *parent);
		~Edges();

		public slots:
		void onControlerPressed();
		void onControlerMoved(EdgeControler::direction, QPoint);
		void onParentResize(Canvas*, QSize);

		Canvas* getParent();

	signals:
		void actEdgeResized(QSize size);
		void actEdgeMoved(QPoint pt);

	private:
		Canvas* mParent;
		QMap<EdgeControler::direction, EdgeControler*> mEdges;

		int thickness, offset, corner, gap;

		QSize mousePressedParentSize;
		QPoint mousePressedOriginCoor;
	};
}

#endif // DUMMY_H