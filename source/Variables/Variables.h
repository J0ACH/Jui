#ifndef VARIABLES_H
#define VARIABLES_H

#include "Text.h"

namespace Jui {

	class Variable : public Canvas {
	public:
		Variable(QWidget *parent = 0);
		
	private:
		//QString label;
		PureText *label, *value;
	};

}

#endif