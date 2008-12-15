/**
 * UnicalcMath.cpp
 *
 * @author John Reese
 */

#include "UnicalcMath.h"

UnicalcMath::UnicalcMath()
{
	historyString = "";
	lastValue = "0";
	currentValue = "0";
	operationCode = MATHOP_NULL;
	useLast = false;
	
	oldOpCode=0;
	
}

QString UnicalcMath::history(){ return historyString; }
QString UnicalcMath::current(){ 
	return currentValue;
}

QString UnicalcMath::last(){
	return lastValue;
}

int UnicalcMath::symbol(){
	return operationCode;
}

void UnicalcMath::press0(){
	appendDigit(0);	
	emit changed();
}

void UnicalcMath::press1(){
	appendDigit(1);	
	emit changed();
}

void UnicalcMath::press2(){
	appendDigit(2);
	emit changed();
}

void UnicalcMath::press3(){
	appendDigit(3);
	emit changed();
}

void UnicalcMath::press4(){
	appendDigit(4);
	emit changed();
}

void UnicalcMath::press5(){
	appendDigit(5);
	emit changed();
}

void UnicalcMath::press6(){
	appendDigit(6);
	emit changed();
}

void UnicalcMath::press7(){
	appendDigit(7);
	emit changed();
}

void UnicalcMath::press8(){
	appendDigit(8);
	emit changed();
}

void UnicalcMath::press9(){
	appendDigit(9);
	emit changed();
}

void UnicalcMath::appendDigit( int digit ){
	if ( currentValue == "0" ){
		currentValue.setNum(digit);
	} else {
		currentValue.append( QString().setNum(digit) );
	}
	useLast=false;
	emit changed();
}

void UnicalcMath::pressDecimal(){ 
	if ( currentValue.contains('.')==0 ){
		currentValue.append(".");
	}
	useLast=false;
	emit changed();
}

void UnicalcMath::pressChangeSign(){
	if ( currentValue.startsWith( "-") ){
		currentValue.remove(0,1);
	} else {
		currentValue.prepend("-");
	}
	useLast=false;
	emit changed();
}

void UnicalcMath::pressPlus(){
	updateValues();
	operationCode = MATHOP_PLUS;
	emit changed();
}
void UnicalcMath::pressMinus(){
	updateValues();
	operationCode = MATHOP_MINUS;
	emit changed();
}

void UnicalcMath::pressMultiply(){
	updateValues();
	operationCode = MATHOP_MULTIPLY;
	emit changed();
}

void UnicalcMath::pressDivide(){
	updateValues();
	operationCode = MATHOP_DIVIDE;
	emit changed();
}

void UnicalcMath::pressEquals(){
	updateValues();
	operationCode = MATHOP_EQUALS;
	useLast=true;

	emit changed();
}

void UnicalcMath::pressBackspace(){
	useLast=false;
	currentValue.remove( currentValue.length()-1, 1);
	if ( currentValue.length() == 0 ){
		currentValue = "0";
	}
	emit changed();
}
void UnicalcMath::pressClear(){
	useLast=false;
	currentValue = "0";
	emit changed();
}
void UnicalcMath::pressClearAll(){
	useLast=false;
	currentValue = "0";
	lastValue="0";
	operationCode=MATHOP_EQUALS;
	historyString="";
	emit changed();
}

void UnicalcMath::updateValues(){

	if ( useLast ){
		useLast=false;
		return;
	}

	bool parsed1=false;
	bool parsed2=false;
	double current = currentValue.toDouble(&parsed1);
	double last = lastValue.toDouble(&parsed2);

	if ( !parsed1 || !parsed2){
		emit error("Could not parse number");
		return;
	}


	if ( operationCode != MATHOP_NULL && operationCode != MATHOP_EQUALS){
		historyString.append(lastValue + " " + (char)operationCode + " " + currentValue + " = ");
	}

	useLast=false;

	switch ( operationCode ){
		case MATHOP_EQUALS:
			last=current;
			break;
		case MATHOP_PLUS:
			last+=current;
			break;
		case MATHOP_MINUS:
			last-=current;
			break;
		case MATHOP_MULTIPLY:
			last*=current;
			break;
		case MATHOP_DIVIDE:
			if ( current == 0.0 ) {
				emit error("Cannot divide by 0");
			} else {
				last/=current;
			}
			break;
		default:
			break;
	}
	lastValue.setNum(last,'g',16);
	while ( lastValue[lastValue.length()-1]=='0' ){
		lastValue.remove(lastValue.length()-1,1);
	}
	if ( lastValue[lastValue.length()-1]=='.'){
		lastValue.remove(lastValue.length()-1,1);
	}
	historyString.append("\n" + QString(operationCode) + " " + currentValue + " = " + lastValue );
	currentValue="0";
	
}
// EOF

