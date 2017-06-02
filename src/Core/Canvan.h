#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>

namespace Jui
{
	class Canvan : public QWidget
	{
		//Q_OBJECT

	public:
		Canvan(QWidget *parent, int x, int y, int width, int height);
		Canvan(int x, int y, int width, int height);
		~Canvan();
		
		void setName(QString name);
		void setBackgroundAlpha(int alpha);
		void setBackgroundColor(int red, int green, int blue);
		void setFrameAlpha(int alpha);
		void setFrameColor(int red, int green, int blue);


	protected:
		void mousePressEvent(QMouseEvent *event);
		void paintEvent(QPaintEvent *event);

	private:
		void init(int x, int y, int width, int height);
			
		QString name;
		QColor colorBackround, colorFrame;
	};
}

