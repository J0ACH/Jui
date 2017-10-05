#include "Canvas.h"

namespace Jui
{
	Canvas::Canvas(QWidget *parent) : QWidget(parent) { Canvas::init(); }
	Canvas::Canvas(QWidget *parent, int x, int y, int w, int h) : QWidget(parent) { Canvas::init(x, y, w, h); }
	Canvas::Canvas(int x, int y, int w, int h) : QWidget(0) { Canvas::init(x, y, w, h); }

	void Canvas::init(int x, int y, int w, int h) {
		setWindowFlags(Qt::FramelessWindowHint);
		//setAttribute(Qt::WA_TranslucentBackground);		
		setGeometry(x, y, w, h);
		show();
	}

	void Canvas::origin_(int x, int y) { QWidget::move(x, y); }
	void Canvas::geometry_(int x, int y, int w, int h) { QWidget::setGeometry(x, y, w, h); }
	QPoint Canvas::origin() {
		if (this->isWindow()) { return this->mapToGlobal(QPoint(0, 0)); }
		else { return this->mapToParent(QPoint(0, 0)); }
	}
	void Canvas::mousePressEvent(QMouseEvent *e) { setFocus(); }
	void Canvas::paintEvent(QPaintEvent *e) {
		QPainter painter(this);
		QRect frameRect = QRect(0, 0, width() - 1, height() - 1);
		QRect fillRect = QRect(0, 0, width(), height());

		painter.fillRect(fillRect, QColor(20, 20, 20));
		painter.setPen(QColor(50, 50, 50));
		painter.drawRect(frameRect);
	}
}
