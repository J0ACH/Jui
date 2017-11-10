#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include "Core.h"

namespace Jui
{

	
	// Point /////////////////////////////////////////////////////

	class Point : public AbstractGeometry
	{
	public:
		Point(Canvas *parent);
		
		void origin_(int x, int y);

		void draw(QPainter *painter);

	private:
		double originX, originY;
		int size;

	};

	// Line /////////////////////////////////////////////////////

	class Line : public AbstractGeometry
	{
	public:
		Line(Canvas* parent);

		void from_(int x, int y);
		void to_(int x, int y);

		void draw(QPainter *painter);

	private:
		QPoint fromPt, toPt;
	};
	
}

#endif // GEOMETRY_H