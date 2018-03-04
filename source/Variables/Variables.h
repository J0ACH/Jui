#ifndef VARIABLES_H
#define VARIABLES_H

#include "Text.h"

namespace Jui {

	class Variable : public Canvas {
		Q_OBJECT

	public:
		Variable(QWidget *parent);
		void label_(QString txt);
		void text_(QString val);		
	
	signals:
		void changed();

	private:
		PureText * label, *valText;
	};

	class Vbool : public Variable {
	public:
		Vbool(QWidget *parent);

		void value_(bool ref);
		//bool value();
		bool getValue();

		operator bool() const;
		//void operator =(bool b);
	private:
		bool reference;
	};
}

#endif