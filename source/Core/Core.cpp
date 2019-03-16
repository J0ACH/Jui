#include "Core.h"

namespace Jui
{
	void Jui::loadFonts() {
		int f1 = QFontDatabase::addApplicationFont(":/fontText.ttf");
		int f2 = QFontDatabase::addApplicationFont(":/fontConsole.ttf");
	}

	QColor Jui::getWindowsAccentColor() {

		/*
		QSettings reg("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\DWM", QSettings::Registry32Format);
		foreach(QString oneReg, reg.childKeys())
		{
			QVariant var = reg.value(oneReg);
			var.convert(QVariant::UInt);
			QString str = var.toString();
			//QColor color = QColor(str);
			qDebug() << "key: " << oneReg << " value: " << var << " str: " << str;
		}
		*/

		QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\DWM", QSettings::NativeFormat);
		QVariant variant = settings.value("AccentColor");
		variant.convert(QVariant::UInt);
		uint intColor = variant.toInt();
		byte r = (byte)(intColor >> 0);
		byte g = (byte)(intColor >> 8);
		byte b = (byte)(intColor >> 16);
		byte a = (byte)(intColor >> 24);
		QColor color = QColor(r, g, b, a);
		return color;
	}

	// Canvas /////////////////////////////////////////////////////

	Canvas::Canvas(QWidget *parent) : QWidget(parent) { Canvas::init(); }
	Canvas::Canvas(QWidget *parent, int x, int y, int w, int h) : QWidget(parent) { Canvas::init(x, y, w, h); }
	Canvas::Canvas(int x, int y, int w, int h) : QWidget(0) { Canvas::init(x, y, w, h); }

	void Canvas::init(int x, int y, int w, int h) {
		name_("Nan");
		setWindowFlags(Qt::FramelessWindowHint);
		//setAttribute(Qt::WA_TranslucentBackground);		
		setGeometry(x, y, w, h);
		setFocusPolicy(Qt::ClickFocus);
		activeColor = QColor(90, 90, 90);
		show();
	}

	void Canvas::geometry_(int x, int y, int w, int h) { QWidget::setGeometry(x, y, w, h); }
	void Canvas::origin_(int x, int y) { QWidget::move(x, y); }
	void Canvas::originX_(int x) { QWidget::move(x, origin().y()); }
	void Canvas::originY_(int y) { QWidget::move(origin().x(), y); }
	void Canvas::name_(QString txt) { this->setObjectName(txt); }
	void Canvas::colorActive_(QColor color) { activeColor = color; }

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

	// MainCanvas /////////////////////////////////////////////////////

	MainCanvas::MainCanvas(QWidget *parent) : Canvas(parent) { MainCanvas::init(); }
	MainCanvas::MainCanvas(int x, int y, int w, int h) : Canvas(x, y, w, h) { MainCanvas::init(); }

	void MainCanvas::init() {
		setWindowFlags(Qt::CustomizeWindowHint);
		//setGeometry(x, y, w, h);
		//show();
	}



}

