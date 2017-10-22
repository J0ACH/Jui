#include "Button.h"

namespace Jui
{

	// Button /////////////////////////////////////////////////////

	Button::Button(QWidget *parent) : Canvas(parent) {
		isPressable = false;
		isChecked = false;
		text = "OFF";
		colorFrame.value_(QColor(0, 0, 0, 0));
		colorImage.value_(50, 50, 50);
		colorBackground.value_(QColor(0, 0, 0, 0));
		connect(
			&colorFrame, SIGNAL(changed()),
			this, SLOT(update())
		);
		connect(
			&colorBackground, SIGNAL(changed()),
			this, SLOT(update())
		);
	}
	void Button::label_(QString txt) { text = txt; }
	void Button::pressable_(bool b) { isPressable = b; }
	void Button::icon_(const char* img, int offset) {
		icon = QImage(img);
		iconOffset = offset;
	}

	void Button::enterEvent(QEvent *e) {
		colorFrame.value_(200, 200, 200, 0.2);
		colorImage.value_(200, 200, 200, 0.2);
	}
	void Button::leaveEvent(QEvent *e) {
		colorFrame.value_(QColor(0, 0, 0, 0), 1);
		colorImage.value_(50, 50, 50, 1);
	}
	void Button::mousePressEvent(QMouseEvent *e) {
		if (!isChecked) {
			isChecked = true;
			colorBackground.value_(120, 20, 20, 0.05);
			text = "ON";
		}
		else
		{
			isChecked = false;
			colorBackground.value_(QColor(0, 0, 0, 0), 0.05);
			text = "OFF";
		}
		emit pressed();
	}
	void Button::mouseReleaseEvent(QMouseEvent *e) {
		if (isChecked) {
			if (!isPressable) {
				isChecked = false;
				colorBackground.value_(QColor(0, 0, 0, 0), 0.5);
				text = "OFF";
			}
		}
	}

	void Button::paintEvent(QPaintEvent *e) {
		QPainter painter(this);

		QRect frameRect = QRect(0, 0, width() - 1, height() - 1);
		QRect fillRect = QRect(0, 0, width(), height());

		painter.fillRect(fillRect, colorBackground);

		if (icon.isNull()) {
			painter.setPen(colorFrame);
			painter.drawRect(frameRect);
			painter.setPen(colorImage);
			painter.drawText(rect(), Qt::AlignCenter, text);
		}
		else {
			float moveX = (this->width() - icon.width()) / 2;
			float moveY = (this->height() - icon.height()) / 2;

			QRectF target(moveX, moveY, icon.width(), icon.height());
			QRectF source(0, 0, icon.width(), icon.height());

			QImage renderedIcon(icon);
			renderedIcon.fill(colorImage);
			renderedIcon.setAlphaChannel(icon);
			painter.drawImage(target, renderedIcon, source);  // draw image to QWidget
		}
	}

	// NumberBox /////////////////////////////////////////////////////

	NumberBox::NumberBox(QWidget *parent) : Canvas(parent),
		label(new PureText(this)),
		current(new PureText(this)),
		target(new LineText(this)),
		fadetime(new LineText(this))
	{
		cntDecNums = 2;
		//variable.value_(0);
		//variable.reciever(this, "onCurrentChanged");


		label->geometry_(5, 5, 139, 16);
		label->text_("value");
		label->align_(Qt::AlignRight | Qt::AlignVCenter);

		current->geometry_(5, 20, 140, 60);
		current->align_(Qt::AlignRight | Qt::AlignVCenter);

		target->geometry_(150, 27, 40, 20);
		target->text_("0");
		target->align_(Qt::AlignRight | Qt::AlignVCenter);

		fadetime->geometry_(150, 50, 40, 20);
		fadetime->text_("0");
		fadetime->align_(Qt::AlignRight | Qt::AlignVCenter);

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
		//variable.value_(0);
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

	// StringBox /////////////////////////////////////////////////////

	StringBox::StringBox(QWidget *parent) : Canvas(parent),
		label(new PureText(this)),
		txt(new LineText(this))
	{
		label->geometry_(5, 5, 139, 16);
		label->text_("value");
		label->align_(Qt::AlignLeft | Qt::AlignVCenter);

		txt->geometry_(5, 20, 140, 60);
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

	void StringBox::onSet() {
		emit changed();
	}
}

