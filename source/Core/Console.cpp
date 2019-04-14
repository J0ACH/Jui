#include "Console.h"

namespace Jui
{
	Console::Console(QWidget *parent) : QWidget(parent) { this->init(10, 10, 400, 400); }
	Console::Console(QWidget *parent, int x, int y, int w, int h) : QWidget(parent) { Console::init(x, y, w, h); }
	Console::Console(int x, int y, int w, int h) : QWidget(nullptr) { Console::init(x, y, w, h); }

	void Console::init(int x, int y, int w, int h) {

		setObjectName("Console");

		scroll = new QScrollArea(this);
		//scroll->setGeometry(10, 10, 300, 300);
		scroll->setWidget(new QWidget());
		scroll->setWidgetResizable(true);
		scroll->setFrameStyle(0);
		//scroll->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
		/*
		scroll->verticalScrollBar()->setStyleSheet(
			"QScrollBar::up - arrow:vertical, QScrollBar::bottom - arrow : vertical"
			"{"
			"border: none;"
			"background: none;"
			"color: none;"
			"}"
		);
		*/
		
		size = 100;
		QList<QLabel*> lines;

		lineHeight = 30;

		setGeometry(x, y, w, h);
		//show();
	}

	void Console::println(QString msg) {
		QLabel *label = new QLabel(scroll->widget());
		label->setGeometry(10, 10, 200, lineHeight);
		label->setFont(QFont("Segoe UI Light", 7));
		label->setText(msg);
		label->show();

		lines.append(label);

		//qDebug() << lines.length() << " > " << size;

		if (lines.length() > size) {
			lines.takeFirst()->deleteLater();

			//QLabel *firstOne = lines.takeFirst();
			//firstOne->deleteLater();
		}

		int posY = 0;
		foreach(QLabel *oneLabel, lines)
		{
			oneLabel->move(oneLabel->x(), posY);
			posY += lineHeight;
		}

		scroll->widget()->setFixedHeight(posY);
		scroll->ensureWidgetVisible(label);

	}

	void Console::resizeEvent(QResizeEvent *e) {
		QWidget::resizeEvent(e);
		scroll->setGeometry(10, 10, width() - 20, height() - 20);
		println(QString("resized: %1x%2").arg(
			QString::number(scroll->width()),
			QString::number(scroll->height())
		));
		//emit resized(size());
	}
}