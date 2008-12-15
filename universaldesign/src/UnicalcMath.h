#ifndef UNICALC_MATH_H
#define UNICALC_MATH_H

/**
 * UnicalcMath.h
 * Object handling all the math functions
 *
 * @author John Reese
 */

#include <QtGui>

class UnicalcMath : public QObject
{
	Q_OBJECT

public:
	UnicalcMath();

	QString history();
	QString current();
	QString last();
	int symbol();

	static const int MATHOP_EQUALS = '=';
	static const int MATHOP_PLUS = '+';
	static const int MATHOP_MINUS = '-';
	static const int MATHOP_MULTIPLY = '*';
	static const int MATHOP_DIVIDE = '/';
	static const int MATHOP_NULL = 0;

signals:
	void changed();
	void error();
	void error(QString desc);
	void result();

public slots:
	void press0();
	void press1();
	void press2();
	void press3();
	void press4();
	void press5();
	void press6();
	void press7();
	void press8();
	void press9();

	void pressDecimal();
	void pressChangeSign();
	void pressPlus();
	void pressMinus();
	void pressMultiply();
	void pressDivide();
	void pressEquals();

	void pressBackspace();
	void pressClear();
	void pressClearAll();

private:
	void updateValues();
	void appendDigit(int digit);

	QString historyString;
	QString lastValue;
	QString currentValue;
	int operationCode;
	int oldOpCode;

	bool useLast;

};

#endif //UNICALC_MATH_H

//EOF

