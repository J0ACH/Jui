#include "Screens.h"

namespace Jui
{

	// Win /////////////////////////////////////////////////////

	Win::Win(int x, int y, int w, int h) : Canvas(nullptr),
		winHeader(new Header(this)),
		winEdges(new Edges(this)),
		buttonClose(new Button(this)),
		buttonMaximize(new Button(this)),
		buttonMinimize(new Button(this))
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
	}

	void Win::name_(QString name) { winHeader->name_(name); }
	
	void Win::onParentResize(QSize size) {
		buttonClose->geometry_(size.width() - 40, 0, 40, 40);
		buttonMaximize->geometry_(size.width() - 80, 0, 40, 40);
		buttonMinimize->geometry_(size.width() - 120, 0, 40, 40);
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
		buttonClose->geometry_(size.width() - 25, 5, 20, 20);
	}

}


