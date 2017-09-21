#ifndef DUMMY_H
#define DUMMY_H

#include "Canvas.h"
#include "Button.h"

namespace Jui
{
	// Header /////////////////////////////////////////////////////

	class Header : public Button
	{
	public:
		Header(QWidget *parent);
	protected:
		void mousePressEvent(QMouseEvent *e) override;
		void mouseMoveEvent(QMouseEvent *e) override;
		bool eventFilter(QObject *object, QEvent *e) override;
		void paintEvent(QPaintEvent *e) override;
	private:
		QWidget* m_parent;
		void fitSize();
		int thickness;
		QPoint mousePressedGlobalCoor, mousePressedOriginCoor;
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

	// EdgeControler2 /////////////////////////////////////////////////////

	class EdgeControler2 : public Button
	{
		Q_OBJECT

	public:
		EdgeControler2(QWidget *parent, Jui::direction dir);
		Jui::direction direction();

	signals:
		void actControlerMoved(Jui::direction, QPoint deltaPt);

	protected:
		void mousePressEvent(QMouseEvent *e) override;
		void mouseMoveEvent(QMouseEvent *e) override;
		void paintEvent(QPaintEvent *e) override;
	private:
		Jui::direction m_direction;
		QPoint mousePressedGlobalCoor;
		
	};

	// Edges2 ///////////////////////////////////////////////////// 

	class Edges2 : public QObject {
		Q_OBJECT
	public:
		Edges2(QWidget *parent);

		public slots:
		void onControlerPressed();
		void onControlerMoved(Jui::direction, QPoint);

	protected:
		bool eventFilter(QObject *object, QEvent *e) override;

	private:
		QWidget* m_parent;
		QMap<Jui::direction, EdgeControler2*> mEdges;
		int thickness, offset, corner, gap;

		void fitSize();

		QSize mousePressedParentSize;
		QPoint mousePressedOriginCoor;

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