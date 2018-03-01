
#include "Variables.h"

namespace Jui {

	Variable::Variable(QWidget *parent) : Canvas(parent) {
		label = new PureText(this);
		label->geometry_(10, 10, 50, 16);
		label->text_("variable");

		valText = new PureText(this);
		valText->geometry_(50, 10, 50, 16);
	}

	void Variable::label_(QString name) { label->text_(name); }
	void Variable::text_(QString val) {
		if (val != valText->text) {
			valText->text_(val);
			emit changed();
		}
	}

	Vbool::Vbool(QWidget *parent) : Variable(parent) {
		reference = false;
	}

	void Vbool::value_(bool ref) {
		reference = ref;
		text_(QString::number(reference));
	}
	bool Vbool::value() { return reference; }
}
