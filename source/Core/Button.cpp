#include "Button.h"

namespace Jui
{
	
	// NumberBox /////////////////////////////////////////////////////

	NumberBox::NumberBox(QWidget *parent) : Canvas(parent),
		label(new PureText(this)),
		current(new PureText(this)),
		target(new LineText(this)),
		fadetime(new LineText(this))
	{
		cntDecNums = 2;
		
		label->text_("value");
		label->align_(Qt::AlignRight | Qt::AlignVCenter);

		current->align_(Qt::AlignRight | Qt::AlignBottom);

		target->text_("0");
		target->align_(Qt::AlignRight | Qt::AlignTop);

		fadetime->text_("0");
		fadetime->align_(Qt::AlignRight | Qt::AlignBottom);

		connect(
			target, SIGNAL(enterPressed()),
			this, SLOT(onSet())
		);
		connect(
			fadetime, SIGNAL(enterPressed()),
			this, SLOT(onSet())
		);
		connect(
			&variable, SIGNAL(changed()),
			this, SLOT(onCurrentChanged())
		);
		connect(
			&variable, SIGNAL(finished()),
			this, SLOT(onFinished())
		);
		onSet();

	}
	double NumberBox::value() { return variable; }
	void NumberBox::text_(QString text) { label->text_(text); }
	void NumberBox::decimalNumbers_(int cnt) { cntDecNums = cnt; }

	void NumberBox::onSet() {
		double newTarget = target->text.toDouble();
		double newFTime = fadetime->text.toDouble();
		startTime = QDateTime::currentMSecsSinceEpoch();
		emit started();
		/*
			qDebug() << tr("NumberBox::onSet (target = %1 fTime = %2)").arg(
				QString::number(newTarget),
				QString::number(newFTime)
			);
		*/
		variable.value_(newTarget, newFTime);
	}
	void NumberBox::onCurrentChanged() {
		QString strVal = QString::number(variable.value(), 'f', cntDecNums);
		current->text_(strVal);
		double currentVal = variable;
		//	qDebug() << tr("NumberBox::onCurrentChanged (value = %1)").arg(QString::number(currentVal));
		emit changed();
	}
	void NumberBox::onFinished() {
		QString strVal = QString::number(variable.value(), 'f', cntDecNums);
		current->text_(strVal);
		emit finished();
		/*
			qDebug() << tr("NumberBox::onFinished (real fadeTime = %1)").arg(
				QString::number(QDateTime::currentMSecsSinceEpoch() - startTime)
			);
		*/
	}
	void NumberBox::resizeEvent(QResizeEvent *e) {
		int w = e->size().width();
		int h = e->size().height();
		label->geometry_(5, 5, w*0.75, 16);
		current->geometry_(5, 21, w*0.75, h - 31);
		target->geometry_(w*0.75 + 5, 21, w * 0.2, (h - 31) / 2);
		fadetime->geometry_(w*0.75 + 5, 50, w * 0.2, (h - 31) / 2);
		Canvas::resizeEvent(e);
	}
	// StringBox /////////////////////////////////////////////////////

	StringBox::StringBox(QWidget *parent) : Canvas(parent),
		label(new PureText(this)),
		txt(new LineText(this))
	{
		label->text_("value");
		label->align_(Qt::AlignLeft | Qt::AlignVCenter);
		txt->align_(Qt::AlignLeft | Qt::AlignVCenter);
		connect(
			txt, SIGNAL(enterPressed()),
			this, SLOT(onSet())
		);
	}

	void StringBox::label_(QString text) {

	}
	void StringBox::text_(QString text) {

	}
	QString StringBox::value() { return txt->text; }

	void StringBox::resizeEvent(QResizeEvent *e) {
		int w = e->size().width();
		int h = e->size().height();
		label->geometry_(5, 5, w / 2 - 10, 16);
		txt->geometry_(5, 21, w - 10, h - 31);
		Canvas::resizeEvent(e);
	}

	void StringBox::onSet() {
		emit changed();
	}
}

