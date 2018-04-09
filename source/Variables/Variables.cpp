
#include "Variables.h"

namespace Jui {

	Variable::Variable(QWidget *parent) : Canvas(parent) {
		
		this->setVisible(false);
		
		label = new PureText(this);
		label->geometry_(10, 10, 50, 16);
		label->text_("variable");

		valText = new PureText(this);
		valText->geometry_(50, 10, 250, 16);
	}

	void Variable::parent_(QWidget *parent) {
		this->setParent(parent);
		this->show();
	}
	void Variable::label_(QString name) { label->text_(name); }
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
		QSize size = e->size();
		label->geometry_(10, 10, 50, 16);
		valText->geometry_(50, 10, size.width()-50, 16);

		Canvas::resizeEvent(e);
		
	}

	// Vbool ///////////////////////////////////////////////

	Vbool::Vbool() : Variable(0) {
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

	Vint::Vint() : Variable(0) {
		reference = 0;
		label_("int");
		text_(QString::number(0));
	}
	void Vint::operator =(int i) {
		reference = i;
		text_(QString::number(reference));
	}
	Vint::operator int() { return reference; }

	// Vstring ///////////////////////////////////////////////

	Vstring::Vstring() : Variable(0) {
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
