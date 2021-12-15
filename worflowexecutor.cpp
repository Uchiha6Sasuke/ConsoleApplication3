#include "wrkfl.h"
#include <iostream>
#include "Calculator.h"
int main(){
    Calculator calc(__argv[1]);
    calc.Calculate();
}