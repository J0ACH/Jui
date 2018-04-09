
#include "Variables.h"

namespace Jui {

	Variable::Variable(QWidget *parent) : Canvas(parent) {
		
		this->setVisible(false);
		
		label = new PureText(this);
		label->geometry_(10, 10, 50, 16);
		label->text_("variable");

		valText = new PureText(this);
		valText->geometry_(50, 10, 50, 16);
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

	// Vbool ///////////////////////////////////////////////

	Vbool::Vbool() : Variable(0) {
		reference = false;
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
		text_(QString::number(0));
	}
	void Vint::operator =(int i) {
		reference = i;
		text_(QString::number(reference));
	}
	Vint::operator int() { return reference; }
}
