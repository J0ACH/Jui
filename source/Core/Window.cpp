#include "Window.h"

namespace Jui
{

	// Screen /////////////////////////////////////////////////////

	Screen::Screen(QWidget *parent) : QWidget(parent) {
		QRect screenRect = QDesktopWidget().availableGeometry(0);
		setGeometry(screenRect);
		setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
		setAttribute(Qt::WA_TranslucentBackground);
		setAttribute(Qt::WA_TransparentForMouseEvents);
		show();
	}

	void Screen::paintEvent(QPaintEvent *e) {
		/*
		QPainter painter(this);
		QRect frameRect = QRect(0, 0, width() - 1, height() - 1);
		painter.setPen(QColor(255, 0, 0));
		painter.drawRect(frameRect);
		*/
	}


	// WindowButton /////////////////////////////////////////////////////

	WindowButton::WindowButton(QWidget *parent) : QPushButton(parent) {
		setFont(QFont("Segoe MDL2 Assets", 8));
		setFlat(true);
		setFocusPolicy(Qt::FocusPolicy::NoFocus);
	}

	void WindowButton::paintEvent(QPaintEvent *e) {

		QPainter painter(this);
		QRect frameRect = QRect(0, 0, width() - 1, height() - 1);
		painter.setPen(QColor(255, 0, 0));
		//painter.drawRect(frameRect);

		QPushButton::paintEvent(e);
	}

	// Window /////////////////////////////////////////////////////

	Window::Window(QWidget *parent) : QMainWindow(nullptr) { Window::init(500, 500); }
	Window::Window(int w, int h) : QMainWindow(nullptr) { Window::init(w, h); }

	void Window::init(int w, int h) {
		scr = new Screen(nullptr);
		setParent(scr);
		setGeometry(scr->width() / 2 - w / 2, scr->height() / 2 - h / 2, w, h);
		setHeaderWidth(46);

		title = new QLabel(this);
		title->setGeometry(15, 5, 200, 35);

		setContentsMargins(QMargins(20, 20, 20, 20));
		QGraphicsDropShadowEffect *windowShadow = new QGraphicsDropShadowEffect;
		windowShadow->setBlurRadius(20);
		windowShadow->setColor(QColor(0, 0, 0));
		windowShadow->setOffset(0);
		setGraphicsEffect(windowShadow);

		setFocusPolicy(Qt::ClickFocus);
		setFocus();

		closeButton = new WindowButton(this);
		closeButton->setText(u8"\uE106");
		
		connect(closeButton, SIGNAL(pressed()), scr, SLOT(close()));

		show();
	}

	void Window::setHeaderWidth(int w) { headerRect.setHeight(w); }
	void Window::setTitle(QString txt) { title->setText(txt); }

	void Window::mousePressEvent(QMouseEvent *e)
	{
		if (headerRect.contains(e->localPos().toPoint())) { isMoving = true; }

		mousePressedGlobalCoor = e->globalPos();
		mousePressedOriginCoor = mapToGlobal(QPoint(0, 0));
	}
	void Window::mouseMoveEvent(QMouseEvent *e)
	{
		QPoint deltaPt(
			e->globalPos().x() - mousePressedGlobalCoor.x(),
			e->globalPos().y() - mousePressedGlobalCoor.y()
		);
		QPoint newOrigin(
			mousePressedOriginCoor.x() + deltaPt.x(),
			mousePressedOriginCoor.y() + deltaPt.y()
		);

		if (isMoving) { move(newOrigin); }
	}
	void Window::mouseReleaseEvent(QMouseEvent *e) { isMoving = false; }

	void Window::resizeEvent(QResizeEvent *e) {
		headerRect = QRect(0, 0, width(), headerRect.height());
		closeButton->setGeometry(width() - headerRect.height()*1.5, 0, headerRect.height()*1.5, headerRect.height());
	}

	void Window::paintEvent(QPaintEvent *e) {
		QPainter painter(this);

		QRect frameRect = QRect(0, 0, width() - 1, height() - 1);
		QRect fillRect = QRect(0, 0, width(), height());

		painter.fillRect(fillRect, palette().color(QPalette::ColorRole::Window));

		QColor frameColor;
		if (hasFocus()) { frameColor = palette().color(QPalette::ColorGroup::Active, QPalette::ColorRole::Highlight); }
		else { frameColor = palette().color(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Highlight); }
		painter.fillRect(headerRect, frameColor);

	}


}