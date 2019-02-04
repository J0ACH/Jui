#include "Console.h"

namespace Jui
{
	Console::Console(QWidget *parent) { this->init(100, 100, 400, 400); }

	void Console::init(int x, int y, int w, int h) {

		scroll = new QScrollArea(this);
		scroll->setGeometry(10, 10, 300, 300);
		scroll->setWidget(new QWidget());
		scroll->setWidgetResizable(true);
		size = 20;
		QList<QLabel*> lines;

		lineHeight = 30;

		setGeometry(x, y, w, h);
		//show();
	}

	void Console::println(QString msg) {
		QLabel *label = new QLabel(scroll->widget());
		label->setGeometry(10, 10, 200, lineHeight);
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
}