#ifndef OPERATOR
#include "math_operations.h"

Calculator::Calculator(int a, int b) : a(a), b(b) {};
int Calculator::add() { return a + b; }
int Calculator::subtract() { return a - b; }
#endif