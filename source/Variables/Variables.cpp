
#include "Variables.h"

namespace Jui {

	Variable::Variable(QWidget *parent) : Canvas(parent) {
		label = new PureText(this);
		label->text_("var = true");
		label->geometry_(10, 10, 50, 16);
	}

}
