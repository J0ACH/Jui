#include "Core.h"

namespace Jui
{
	void Jui::loadFonts() {
		int f1 = QFontDatabase::addApplicationFont(":/fontText.ttf");
		int f2 = QFontDatabase::addApplicationFont(":/fontConsole.ttf");
	}

	// Canvas /////////////////////////////////////////////////////

	Canvas::Canvas(QWidget *parent) : QWidget(parent) { Canvas::init(); }
	Canvas::Canvas(QWidget *parent, int x, int y, int w, int h) : QWidget(parent) { Canvas::init(x, y, w, h); }
	Canvas::Canvas(int x, int y, int w, int h) : QWidget(0) { Canvas::init(x, y, w, h); }

	void Canvas::init(int x, int y, int w, int h) {
		name_("Nan");
		//setWindowFlags(Qt::FramelessWindowHint);
		//setAttribute(Qt::WA_TranslucentBackground);		
		setGeometry(x, y, w, h);
		setFocusPolicy(Qt::ClickFocus);
		show();
	}

	void Canvas::geometry_(int x, int y, int w, int h) { QWidget::setGeometry(x, y, w, h); }
	void Canvas::origin_(int x, int y) { QWidget::move(x, y); }
	void Canvas::originX_(int x) { QWidget::move(x, origin().y()); }
	void Canvas::originY_(int y) { QWidget::move(origin().x(), y); }
	void Canvas::name_(QString txt) { this->setObjectName(txt); }

	QPoint Canvas::origin() {
		if (this->isWindow()) { return this->mapToGlobal(QPoint(0, 0)); }
		else { return this->mapToParent(QPoint(0, 0)); }
	}

	QString Canvas::name() { return this->objectName(); }

	void Canvas::addGeometry(AbstractGeometry *obj) {
		geometryObjects.append(obj);
	}

	void Canvas::resizeEvent(QResizeEvent *e) {
		QWidget::resizeEvent(e);
		emit resized(size());
	}
	void Canvas::paintEvent(QPaintEvent *e) {
		QPainter painter(this);

		QRect frameRect = QRect(0, 0, width() - 1, height() - 1);
		QRect fillRect = QRect(0, 0, width(), height());

		painter.fillRect(fillRect, palette().color(QPalette::ColorRole::Window));

		QColor frameColor;
		if (hasFocus()) { frameColor = palette().color(QPalette::ColorGroup::Active, QPalette::ColorRole::Highlight); }
		else { frameColor = palette().color(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Highlight); }
		painter.setPen(frameColor);

		painter.drawRect(frameRect);

		foreach(AbstractGeometry *oneGeo, geometryObjects)
		{
			oneGeo->draw(&painter);
			oneGeo->drawBBox(&painter);
		}


		//draw(&painter);
	}

	// MainCanvas /////////////////////////////////////////////////////

	MainCanvas::MainCanvas(QWidget *parent) : QWidget(nullptr) { MainCanvas::init(); }
	MainCanvas::MainCanvas(int x, int y, int w, int h) : QWidget(nullptr) {
		setGeometry(x, y, w, h);
		MainCanvas::init();
	}

	void MainCanvas::init() {
		//setWindowFlag(Qt::Window);
		//setWindowFlag(Qt::CustomizeWindowHint);
		//setWindowFlag(Qt::WindowStaysOnTopHint);
		//QRect screenRect = QPlatformScreen() ::::availableGeometry();
		shadowPlane = new QWidget(nullptr);
		shadowPlane->setGeometry(QApplication::desktop()->availableGeometry(0));
		shadowPlane->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
		shadowPlane->setAttribute(Qt::WA_TranslucentBackground);
		setParent(shadowPlane);
		
		//setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
		setFocusPolicy(Qt::ClickFocus);
		setFocus();

		isMoving = false;

		title = new QLabel(this);
		title->setText("MainCanvas");
		//title->setFrameStyle(QFrame::Box | QFrame::Raised);

		headerRect = QRect(0, 0, width(), 10);

		setHeaderWidth(46);
		setHeaderOffset(5);

		setContentsMargins(QMargins(20, 20, 20, 20));
		QGraphicsDropShadowEffect *windowShadow = new QGraphicsDropShadowEffect;
		windowShadow->setBlurRadius(20);
		windowShadow->setColor(QColor(0, 0, 0));
		windowShadow->setOffset(0);
		this->setGraphicsEffect(windowShadow);


		shadowPlane->show();
		show();

		//SetClassWord(hWnd, COLOR_ACTIVECAPTION, RGB(0x00, 0x80, 0x80));
		//Sleep(10000);
		//DestroyWindow(hWnd);
	}

	void MainCanvas::setHeaderWidth(int w) {
		headerRect.setHeight(w);
		headerWidth = w;
	}
	void MainCanvas::setHeaderOffset(int offset) { headerOffset = offset; }

	void MainCanvas::mousePressEvent(QMouseEvent *e)
	{
		if (headerRect.contains(e->localPos().toPoint())) { isMoving = true; }

		mousePressedGlobalCoor = e->globalPos();
		mousePressedOriginCoor = mapToGlobal(QPoint(0, 0));
	}
	void MainCanvas::mouseMoveEvent(QMouseEvent *e)
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
	void MainCanvas::mouseReleaseEvent(QMouseEvent *e) {
		isMoving = false;
	}

	void MainCanvas::resizeEvent(QResizeEvent *e) {
		QWidget::resizeEvent(e);

		headerRect.setWidth(width());


		emit resized(size());
	}
	void MainCanvas::paintEvent(QPaintEvent *e) {


		QPainter painter(this);

		QRect frameRect = QRect(0, 0, width() - 1, height() - 1);
		QRect fillRect = QRect(0, 0, width(), height());

		QRect fillHeader = QRect(0, 0, width(), headerWidth);

		painter.fillRect(fillRect, palette().color(QPalette::ColorRole::Window));

		QColor frameColor;
		if (hasFocus()) { frameColor = palette().color(QPalette::ColorGroup::Active, QPalette::ColorRole::Highlight); }
		else { frameColor = palette().color(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Highlight); }

		painter.fillRect(headerRect, frameColor);
		painter.setPen(frameColor);
		painter.drawRect(frameRect);

		//QFont font = title->font();
		//font.setPixelSize(headerWidth - 2 * headerOffset);
		//title->setFont(font);
		title->setGeometry(headerOffset * 2, headerOffset, 100, headerWidth - 2 * headerOffset);

		//QWidget::paintEvent(e);
	}


	// MainWindow /////////////////////////////////////////////////////

	MainWindow::MainWindow(QWidget *parent) : QMainWindow(nullptr) { MainWindow::init(); }
	MainWindow::MainWindow(int x, int y, int w, int h) : QMainWindow(nullptr) {
		setGeometry(x, y, w, h);
		MainWindow::init();
	}

	void MainWindow::init() {
		//setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
		//setWindowFlags(Qt::Window | Qt::WindowStaysOnTopHint);
		//setWindowFlags(Qt::Sheet | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::CustomizeWindowHint);

		//setAttribute(Qt::WA_NoBackground);

		//setContentsMargins(0, 0, right, bottom);
		hWnd = (HWND)this->winId();
		//DWORD aero_borderless = WS_THICKFRAME | WS_CLIPCHILDREN;
		//DWORD aero_borderless = WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CLIPCHILDREN;
		//SetWindowLong(hWnd, GWL_STYLE, aero_borderless);
		//SetWindowPos(hWnd, 0, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);

		//SetWindowLong((HWND)winId(), GWL_STYLE, GetWindowLong((HWND)winId(), GWL_STYLE)&~WS_SIZEBOX);
		//SetWindowLong((HWND)winId(), GWL_STYLE, WS_CLIPCHILDREN);
		//SetWindowLong((HWND)winId(), GWL_STYLE, WS_BORDER);
		//SetWindowLong((HWND)winId(), GWL_STYLE, WS_THICKFRAME);
		//SetWindowLong((HWND)winId(), GWL_STYLE, WS_CHILD);
		//SetWindowLong((HWND)winId(), GWL_STYLE, WS_EX_WINDOWEDGE);



				//leftSpacer->setAttribute(Qt::WA_TransparentForMouseEvents);

		//toolBar = new QToolBar(this);
		//sBar = new QStatusBar(this);

		//statusBar()->showMessage(tr("Ready"));
		qDebug() << "this->winId() " << this->winId();
		qDebug() << "hWnd " << hWnd;

		SetWindowPos(hWnd, HWND_TOPMOST, 100, 100, 600, 600, SWP_SHOWWINDOW);
		SetWindowTextA(hWnd, "ahoj");

		//show();

		qDebug() << "this->geometry() " << this->geometry().y();
		qDebug() << "this->frameGeometry() " << this->frameGeometry();
		qDebug() << "this->window()->frameSize() " << this->window()->mask();
	}

	bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result) {
		MSG *msg = static_cast<MSG*>(message);

		switch (msg->message)
		{
		case WM_NCPAINT:
			HDC hdc;
			RECT rect, wr;
			LONG right, bottom;
			HBRUSH hBrush = CreateSolidBrush(RGB(100, 180, 180));

			// Undocumented flag works for me
			//hdc = GetDCEx(hWnd, (HRGN)msg->wParam, DCX_WINDOW | DCX_INTERSECTRGN | 0x10000);
			//hdc = GetDCEx(hWnd, (HRGN)msg->wParam, DCX_WINDOW | DCX_INTERSECTRGN);
			hdc = GetDCEx(hWnd, (HRGN)msg->wParam, DCX_WINDOW | DCX_CACHE | DCX_INTERSECTRGN | DCX_LOCKWINDOWUPDATE);

			GetWindowRect(hWnd, &wr);
			right = wr.right - wr.left;
			bottom = wr.bottom - wr.top;

			// various rectangles to try
			// - parameters - SetRect(&rect, left, top, right, bottom);
			SetRect(&rect, 0, 0, right, bottom); // whole window area
			//SetRect(&rect, 0, 30, right, bottom);
			//SetRect(&rect, 0, 0, 150, 150);

			FillRect(hdc, &rect, hBrush);

			ReleaseDC(hWnd, hdc);
			//RedrawWindow(hWnd, &rect, (HRGN)msg->wParam, RDW_UPDATENOW);
			qDebug() << "event WM_NCPAINT: " << msg->hwnd;
			return true;
			break;

		}

		return false;
	}
	void MainWindow::paintEvent(QPaintEvent *e) {
		QPainter painter(this);

		QRect frameRect = QRect(0, 0, width() - 1, height() - 1);
		QRect fillRect = QRect(0, 0, width(), height());

		QRect fillHeader = QRect(0, 0, width(), 46);

		painter.fillRect(fillRect, palette().color(QPalette::ColorRole::Window));

		QColor frameColor;
		if (hasFocus()) { frameColor = palette().color(QPalette::ColorGroup::Active, QPalette::ColorRole::Highlight); }
		else { frameColor = palette().color(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Highlight); }

		painter.fillRect(fillRect, frameColor);
		painter.setPen(frameColor);
		painter.drawRect(frameRect);

		//QFont font = title->font();
		//font.setPixelSize(headerWidth - 2 * headerOffset);
		//title->setFont(font);
		//title->setGeometry(headerOffset * 2, headerOffset, 100, headerWidth - 2 * headerOffset);
	}

	// GraphicsCanvas /////////////////////////////////////////////////////

	GraphicsCanvas::GraphicsCanvas(int w, int h) {
		//setWindowFrameMargins(0, 0, 0, 0);

		scene = new QGraphicsScene();


		//Window *window = new Window;
		//scene.addItem(window);

		view = new QGraphicsView(scene);
		view->resize(w, h);
		view->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
		//view->setLayout(layout);
		view->show();
		view->layout()->margin();
		qDebug() << "thisGraphicsCanvas init";
		//setWindowTitle(tr("Basic Graphics Layouts Example"));

		//QLayout *layout = new QLayout(view);

	}
	/*
	static void paintLayout(QPainter *painter, QLayoutItem *item)
	{
		QLayout *layout = item->layout();
		if (layout) {
			for (int i = 0; i < layout->count(); ++i)
				paintLayout(painter, layout->itemAt(i));
		}
		painter->drawRect(item->geometry());
	}

	void GraphicsCanvas::paintEvent(QPaintEvent *)
	{
		QPainter painter(this);
		if (layout())
			paintLayout(&painter, layout());
	}
	*/


	// AbstractGeometry /////////////////////////////////////////////////////

	AbstractGeometry::AbstractGeometry(Canvas* parent) :
		m_parent(parent)
	{
		m_parent->addGeometry(this);
		m_displayBBox = false;
	}


	void AbstractGeometry::bbox_(QRect rect) { bbox = rect; }
	void AbstractGeometry::displayBBox(bool b) { m_displayBBox = b; }
	void AbstractGeometry::update() { m_parent->update(bbox); }
	void AbstractGeometry::drawBBox(QPainter *painter) {
		if (m_displayBBox) {
			painter->setPen(QColor(255, 0, 0));
			painter->drawRect(bbox);
		}
	}

}

