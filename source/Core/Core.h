#ifndef CORE_H
#define CORE_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include "Fade.h"

namespace Jui
{
	class Canvas;
	class AbstractGeometry;
	
	enum fade { out, in };
	enum direction { right, bottom, left, top };
	void loadFonts();
	QColor getWindowsAccentColor();

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
		void colorActive_(QColor color);

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
		QColor activeColor;
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

	// MainCanvas

	class MainCanvas : public Canvas
	{
		Q_OBJECT

	public:
		MainCanvas(QWidget *parent = 0);
		MainCanvas(int x, int y, int width, int height);
		
	private: 
		//Header titleBar;

		void init();

	};
	
}

#endif // CORE_H