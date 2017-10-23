#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "Core.h"

namespace Jui
{

	// Point /////////////////////////////////////////////////////

	class Point : public Canvas
	{
		Q_OBJECT
			
	public:
		Point(QWidget *parent = 0);

		enum shape { CIRCLE, CROSS };

		void x_(int x);
		void y_(int y);
		void size_(int s);
		
	protected:
		void paintEvent(QPaintEvent *e) override;

	private:
		shape m_shape;
	};

}

#endif // GEOMETRY_H