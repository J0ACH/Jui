#include "canvan.h"

Canvan::Canvan(int originX, int originY, int sizeX, int sizeY)
	: QMainWindow()
{
	setGeometry(QRect(originX, originY, sizeX, sizeY));
	setPalette();

	//setWindowFlags(Qt::CustomizeWindowHint);
	setWindowFlags(Qt::FramelessWindowHint);
	//setIconSize(QSize(100, 100));

	globalCursor = new QPoint(0, 0);
	mCursor = new QPoint(0, 0);

	header = new QWidget(this);
	screen = new QWidget(this);
	//tail = new QStatusBar(this);

	closeButton = new QPushButton(this);
	closeButton->setGeometry(50, 50, 100, 30);
	//closeButton->setFlat(true);

	//testButton = new Button(this);



	setCentralWidget(screen);
	//setStatusBar(tail);


	//console = new QDockWidget(QString("Console"), this);

	dock = new QDockWidget(tr("Console"), this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	/*
	console = new Console(dock);
	dock->setWidget(console);
	addDockWidget(Qt::RightDockWidgetArea, dock);
	*/

	//connect(this, SIGNAL(sendToConsole(QString)), console, SLOT(addLine(QString)));
	connect(closeButton, SIGNAL(pressed()), this, SLOT(closeCanvan()));
	//connect(testButton, SIGNAL(pressAct()), this, SLOT(testUpdate()));

}

void Canvan::msgConsole(QString text)
{
	emit sendToConsole(text);
}

void Canvan::resizeEvent(QResizeEvent *event)
{
	//qDebug() << "Resize canvan";

	//frame = new QRect(0, 0, width() - 1, height() - 1);

	//headerSize = 50;
	//tailSize = 30;
	//headerFrame = new QRect(0, 0, frame->width(), headerSize);
	//centerFrame = new QRect(0, headerSize, frame->width(), frame->height() - headerSize - tailSize);
	//tailFrame = new QRect(0, frame->height() - tailSize, frame->width(), tailSize);

	//headerWidget->setGeometry(*headerFrame);
	/*
	closeButton->setGeometry(width() - 40, 10, 30, 30);
	maximizeButton->setGeometry(width() - 70, 10, 30, 30);
	minimizeButton->setGeometry(width() - 100, 10, 30, 30);

	*/
	testButton->setGeometry(width() - 450, 150, 100, 30);
	QSize size = event->size();

	QString text = tr("resized [%1,%2]").arg(QString::number(size.width()), QString::number(size.height()));
	emit sendToConsole(text);
}
void Canvan::mousePressEvent(QMouseEvent *mouseEvent)
{
	*mCursor = mouseEvent->pos();
	//int mouseX = mCursor->x();
	//int mouseY = mCursor->y() ;
	//QString text = tr("pressed [%1,%2]").arg(QString::number(mouseX), QString::number(mouseY));
	QString text = tr("pressed [%1,%2]").arg(QString::number(mCursor->x()), QString::number(mCursor->y()));
	emit sendToConsole(text);
}
void Canvan::mouseMoveEvent(QMouseEvent *mouseEvent)
{
	//if (mouseEvent->type() == QFlag(mouseM)

	*globalCursor = mouseEvent->globalPos();
	//*mouseButton = mouseEvent->button();
	//*mouseButtons = mouseEvent->buttons();

	setGeometry(globalCursor->x() - mCursor->x(), globalCursor->y() - mCursor->y(), width(), height());

	QString text = QString("move[%1, %2]").arg(QString::number(globalCursor->x()), QString::number(globalCursor->y()));
	emit sendToConsole(text);
	update();
}

void Canvan::setPalette()
{
	backColor = new QBrush(QColor(30, 30, 30), Qt::SolidPattern);
	panelColor = new QBrush(QColor(20, 20, 20), Qt::SolidPattern);
	textColor = new QColor(230, 230, 230);
	activeColor = new QColor(20, 180, 240);

	palette = new QPalette();
	//palette->setBrush(QPalette::Window, QBrush(QColor(30, 30, 30), Qt::SolidPattern));
	//palette->setColor(QPalette::Window, QColor(30, 30, 30));
	palette->setBrush(QPalette::Window, *panelColor);
	palette->setBrush(QPalette::Base, *backColor);

	palette->setColor(QPalette::WindowText, *textColor);
	palette->setColor(QPalette::Text, *textColor);

	palette->setColor(QPalette::Highlight, *activeColor);

	qApp->setPalette(*palette);
}

void Canvan::closeCanvan() { close(); }
void Canvan::minimizeCanvan()
{
	//emit minimizeAct();
	//showMinimized();
}
void Canvan::maximizeCanvan()
{
	//qDebug() << "Maximize canvan";
	//resizeCanvan();
	//emit maximizeAct();
}

Canvan::~Canvan()
{

}

