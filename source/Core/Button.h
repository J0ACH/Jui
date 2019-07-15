#ifndef BUTTON_H
#define BUTTON_H

#include "Core.h"
#include "Fade.h"
#include "Text.h"

namespace Jui
{
	// NumberBox /////////////////////////////////////////////////////

	class NumberBox : public Canvas
	{
		Q_OBJECT

	public:
		NumberBox(QWidget *parent = 0);
		void text_(QString text);
		void decimalNumbers_(int cnt);
		double value();

	signals:
		void started();
		void changed();
		void finished();

	protected:
		void resizeEvent(QResizeEvent *e) override;
		
	private:
		PureText *label, *current;
		LineText *target, *fadetime;
		FadeDouble variable;
		int cntDecNums;
		qint64 startTime;
		
		private slots:
		void onSet();
		void onCurrentChanged();
		void onFinished();
	
	};

	// StringBox /////////////////////////////////////////////////////

	class StringBox : public Canvas
	{
		Q_OBJECT

	public:
		StringBox(QWidget *parent = 0);
		void label_(QString text);
		void text_(QString text);
		QString value();

	signals:
		void changed();

	protected:
		void resizeEvent(QResizeEvent *e) override;

	private:
		PureText *label;
		LineText *txt;
		
		private slots:
		void onSet();
	};
}

#endif // BUTTON_H
