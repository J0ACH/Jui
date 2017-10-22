#ifndef CORE_H
#define CORE_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include "Fade.h"

namespace Jui
{
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

		void origin_(int x, int y);
		void geometry_(int x, int y, int w, int h);
		void name_(QString txt);

		QPoint origin();
		QString name();

	signals:
		void resized(QSize size);

	protected:
		void resizeEvent(QResizeEvent *e) override;
		void paintEvent(QPaintEvent *e) override;

	private:
		//FadePoint m_origin;
		void init(int x = 10, int y = 10, int width = 50, int height = 50);
	};

}

#endif // CORE_H