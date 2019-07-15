#include "Screens.h"

namespace Jui
{
	// Application /////////////////////////////////////////////////////

	Application::Application(int x, int y) : QMainWindow(nullptr, Qt::FramelessWindowHint)
	{
		setGeometry(100, 100, x, y);

		qDebug() << "Application start";
		this->show();
	}

	// Win /////////////////////////////////////////////////////

	Win::Win(int x, int y, int w, int h) : Canvas(nullptr),
		winHeader(new Header(this)),
		winEdges(new Edges(this)),
		buttonClose(new Button(this)),
		buttonMaximize(new Button(this)),
		buttonMinimize(new Button(this)),
		screenWidget(new QWidget(this))
	{
		buttonClose->icon_(":/close16.png");
		buttonMaximize->icon_(":/maximize16.png");
		buttonMinimize->icon_(":/minimize16.png");

		buttonMaximize->pressable_(true);

		connect(
			this, SIGNAL(resized(QSize)),
			this, SLOT(onParentResize(QSize))
		);
		connect(
			buttonClose, SIGNAL(pressed()),
			this, SLOT(close())
		);
		connect(
			buttonMaximize, SIGNAL(pressed()),
			this, SLOT(onMaximize())
		);
		connect(
			buttonMinimize, SIGNAL(pressed()),
			this, SLOT(showMinimized())
		);

		geometry_(x, y, w, h);

		winHeader->height_(40);

		show();
		screenWidget->show();
	}

	void Win::name_(QString name) { winHeader->name_(name); }
	QWidget* Win::widget() { return screenWidget; }
	Win::operator QWidget*() const
	{
		qDebug() << "Win as QWidget";
		return screenWidget;
	}

	void Win::onParentResize(QSize size) {
		buttonClose->setGeometry(size.width() - 40, 0, 40, 40);
		buttonMaximize->setGeometry(size.width() - 80, 0, 40, 40);
		buttonMinimize->setGeometry(size.width() - 120, 0, 40, 40);
		screenWidget->setGeometry(0, winHeader->height(), size.width(), size.height() - winHeader->height());
	}

	void Win::onMaximize() {
		if (!isMaximized()) {
			showMaximized();
			winHeader->lock_(true);
			winEdges->hide();

		}
		else {
			showNormal();
			winHeader->lock_(false);
			winEdges->show();
		}
	}

	// Dialog /////////////////////////////////////////////////////

	Dialog::Dialog(int x, int y, int w, int h) : Canvas(nullptr),
		winHeader(new Header(this)),
		winEdges(new Edges(this)),
		buttonClose(new Button(this))
	{
		buttonClose->icon_(":/close16.png");

		connect(
			this, SIGNAL(resized(QSize)),
			this, SLOT(onParentResize(QSize))
		);
		connect(
			buttonClose, SIGNAL(pressed()),
			this, SLOT(close())
		);

		geometry_(x, y, w, h);
	}

	void Dialog::onParentResize(QSize size) {
		buttonClose->setGeometry(size.width() - 25, 5, 20, 20);
	}

}


