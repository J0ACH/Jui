#include <QWidget>
#include <QPainter>

namespace Jui
{
	class Canvan : public QWidget
	{
	public:
		Canvan(QWidget * parent = 0);
		Canvan(int, int, int, int);
		~Canvan();

	protected:
		void paintEvent(QPaintEvent *event);
	};
}

