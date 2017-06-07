#ifndef CANVAN_H
#define CANVAN_H

#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
//#include <QMetaObject>

//#include "moc_Canvan.cpp"

namespace Jui
{
	class Canvan : public QWidget
	{
		Q_OBJECT

	public:
		Canvan(QWidget *parent, int x, int y, int width, int height);
		Canvan(int x, int y, int width, int height);
		~Canvan();

		void setName(QString name);
		void setBackgroundAlpha(int alpha);
		void setBackgroundColor(int red, int green, int blue);
		void setFrameAlpha(int alpha);
		void setFrameColor(int red, int green, int blue);

	public slots:
		//void onClose();

	signals:
		//void actClosed(Canvan *obj);
		//void actMousePressed(Canvan *obj, int x, int y);
		//void actMousePressed();
		//void actClosed();

	protected:
		void mousePressEvent(QMouseEvent *event);
		void paintEvent(QPaintEvent *event);

	private:
		void init(int x, int y, int width, int height);

		QString name;
		QColor colorBackround, colorFrame;
	};
}



#endif // CANVAN_H
