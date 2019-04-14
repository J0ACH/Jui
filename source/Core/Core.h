#ifndef CORE_H
#define CORE_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
//#include <QGraphicsScene>

#include "Fade.h"

namespace Jui
{
	class Canvas;
	class AbstractGeometry;

	enum fade { out, in };
	enum direction { right, bottom, left, top };
	void loadFonts();

	// Canvas /////////////////////////////////////////////////////

	class Canvas : public QWidget
	{
		Q_OBJECT

	public:
		Canvas(QWidget *parent = 0);
		Canvas(QWidget *parent, int x, int y, int width, int height);
		Canvas(int x, int y, int width, int height);

		void geometry_(int x, int y, int w, int h);
		void origin_(int x, int y);
		void originX_(int x);
		void originY_(int x);
		void name_(QString txt);

		QPoint origin();
		QString name();

		void addGeometry(AbstractGeometry *obj);

	signals:
		void resized(QSize size);

	protected:
		void resizeEvent(QResizeEvent *e) override;
		void paintEvent(QPaintEvent *e) override;

	private:
		//FadePoint m_origin;
		void init(int x = 10, int y = 10, int width = 50, int height = 50);
		QList<AbstractGeometry*> geometryObjects;
	};

	// MainCanvas

	class MainCanvas : public Canvas
	{
		Q_OBJECT

	public:
		MainCanvas(QWidget *parent = 0);
		MainCanvas(int x, int y, int width, int height);

		void setHeaderWidth(int width);
		void setHeaderOffset(int offset);

	signals:
		void resized(QSize size);

	protected:

		void mousePressEvent(QMouseEvent *e) override;
		void mouseMoveEvent(QMouseEvent *e) override;
		void mouseReleaseEvent(QMouseEvent *e) override;

		void resizeEvent(QResizeEvent *e) override;
		void paintEvent(QPaintEvent *e) override;

	private:
		QPoint mousePressedGlobalCoor, mousePressedOriginCoor;
		int headerWidth, headerOffset;
		bool isMoving;

		QRect headerRect;

		QLabel *title;
		QWidget *shadowPlane;
		void init();

	};

	// MainWindow

	class MainWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		MainWindow(QWidget *parent = 0);
		MainWindow(int x, int y, int width, int height);


		//If you want to have Max/Min/Close buttons, look at how QWinWidget uses these 
		QPushButton* maximizeButton = nullptr;
		QPushButton* minimizeButton = nullptr;
		QPushButton* closeButton = nullptr;

		//If you want to enable dragging the window when the mouse is over top of, say, a QToolBar, 
		//then look at how QWinWidget uses this
		QToolBar* toolBar = nullptr;
		QStatusBar* sBar = nullptr;

	signals:

	public slots:

	private:
		void init();

	};


	// GraphicsCanvas

	class GraphicsCanvas : public QGraphicsScene
	{
	public:
		GraphicsCanvas(QObject* parent = 0);
		//GraphicsCanvas(QGraphicsItem* parent = 0, Qt::WindowFlags wFlags = 0);

		//paintWindowFrame(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0)
		//void QGraphicsWidget::paintWindowFrame(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0)
	};


	// AbstractGeometry /////////////////////////////////////////////////////

	class AbstractGeometry
	{
	public:
		AbstractGeometry(Canvas *parent);

		void bbox_(QRect rect);
		void displayBBox(bool b);

		virtual void draw(QPainter *painter) {};
		void drawBBox(QPainter *painter);

	protected:
		void update();

	private:
		Canvas *m_parent;
		QRect bbox;
		bool m_displayBBox;
	};



}

#endif // CORE_H