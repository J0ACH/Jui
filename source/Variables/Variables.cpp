
#include "Variables.h"

namespace Jui {

	Variable::Variable() : Canvas(0) {

		this->setVisible(false);

		this->width_(150);
		this->height_(20);

		labelWidth = 50;
		textOffset = 2;

		label = new PureText(this);
		label->text_("variable");
		label->align_(Qt::AlignLeft);
		//label->displayFrame_(true);

		valText = new PureText(this);
		valText->align_(Qt::AlignLeft);
		//valText->displayFrame_(true);
	}

	void Variable::parent_(QWidget *parent) {
		this->setParent(parent);
		this->show();
	}
	void Variable::label_(QString name) { label->text_(name); }
	void Variable::labelSize_(int x) {
		labelWidth = x;
		fitText();
	}
	void Variable::text_(QString val) {
		//if (val != valText->text) {
		valText->text_(val);
		emit changed();
		//}
	}

	void Variable::connectOnChange(const QObject *receiver, const char *method) {
		QObject::connect(this, SIGNAL(changed()), receiver, method);
	}

	void Variable::resizeEvent(QResizeEvent *e) {
		Canvas::resizeEvent(e);
		fitText();
	}

	void Variable::fitText() {
		int w = this->width();
		int h = this->height();

		label->geometry_(textOffset, textOffset, labelWidth, h - 2 * textOffset);
		valText->geometry_(
			labelWidth + 2 * textOffset,
			textOffset,
			this->width() - labelWidth - 3 * textOffset,
			h - 2 * textOffset
		);
	}

	// Vbool ///////////////////////////////////////////////

	Vbool::Vbool() : Variable() {
		reference = false;
		label_("boolean");
		text_("false");
	}
	void Vbool::operator =(bool b) {
		reference = b;
		if (reference) { text_("true"); }
		else { text_("false"); }
	}
	Vbool::operator bool() { return reference; }

	// Vint ///////////////////////////////////////////////

	Vint::Vint() : Variable() {
		reference = 0;
		label_("int");
		text_(QString::number(0));
	}
	void Vint::operator =(int i) {
		reference = i;
		text_(QString::number(reference));
	}
	/*
	void Vint::operator +(int i) {
		reference += i;
		text_(QString::number(reference));
	}
	void Vint::operator =(Vint i) {
		reference = i;
		text_(QString::number(reference));
	}
	*/

	Vint::operator int() { return reference; }

	// Vstring ///////////////////////////////////////////////

	Vstring::Vstring() : Variable() {
		reference = "";
		label_("string");
		text_("");
	}
	void Vstring::operator =(QString txt) {
		reference = txt;
		text_(reference);
	}
	Vstring::operator QString() { return reference; }
}
