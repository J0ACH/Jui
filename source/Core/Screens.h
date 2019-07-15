#ifndef WINDOWS_H
#define WINDOWS_H

#include "Core.h"
#include "Fade.h"
#include "Dummies.h"
#include "Button.h"
#include "Controls.h"

namespace Jui
{

	// Win /////////////////////////////////////////////////////

	class Application : public QMainWindow
	{
		Q_OBJECT

	public:
		Application(int w, int h);
	};

	// Win /////////////////////////////////////////////////////

	class Win : public Canvas
	{
		Q_OBJECT

	public:
		Win(int x, int y, int w, int h);

		void name_(QString txt);
		QWidget* widget();
		operator QWidget*() const;

	private:
		Header *winHeader;
		Edges *winEdges;
		Button *buttonClose, *buttonMaximize, *buttonMinimize;
		QWidget *screenWidget;

	private slots:
		void onParentResize(QSize size);
		void onMaximize();


	};

	// Dialog /////////////////////////////////////////////////////

	class Dialog : public Canvas
	{
		Q_OBJECT

	public:
		Dialog(int x, int y, int w, int h);

	private:
		Header *winHeader;
		Edges *winEdges;
		Button *buttonClose;

	private slots:
		void onParentResize(QSize size);
	};
}

#endif // WINDOWS_H
