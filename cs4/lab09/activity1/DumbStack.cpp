#include "DumbStack.h"

namespace RITCS{DumbStack::DumbStack(){}DumbStack::~DumbStack(){} char
DumbStack::top()const {return '0';}bool DumbStack::full()const{return
false;}unsigned int DumbStack::size()const{return 1;}void
DumbStack::push(char) {}void DumbStack::pop(){}}

