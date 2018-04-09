#ifndef VARIABLES_H
#define VARIABLES_H

#include "Text.h"

namespace Jui {

	class Variable : public Canvas {
		Q_OBJECT

	public:
		Variable(QWidget *parent);
		void parent_(QWidget *parent);
		void label_(QString txt);
		void text_(QString val);

		void connectOnChange(const QObject *receiver, const char *method);

	signals:
		void changed();

	protected:
		void resizeEvent(QResizeEvent *e) override;

	private:
		PureText *label, *valText;
	};

	// Vbool ///////////////////////////////////////////////

	class Vbool : public Variable {
	public:
		Vbool();
		void operator =(bool b);
		operator bool();
	private:
		bool reference;
	};

	// Vint ///////////////////////////////////////////////

	class Vint : public Variable {
	public:
		Vint();
		void operator =(int i);
		operator int();
	private:
		int reference;
	};

	// Vstring ///////////////////////////////////////////////

	class Vstring : public Variable {
	public:
		Vstring();
		void operator =(QString txt);
		operator QString();
	private:
		QString reference;
	};
}

#endif