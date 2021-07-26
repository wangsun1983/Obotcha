#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Boolean.hpp"
#include "StrongPointer.hpp"
#include "IllegalArgumentException.hpp"

using namespace obotcha;

extern int basetest();
extern int testequals();
extern int testLogic();
extern int testUpdate();
extern int testparse();

int main() {
    basetest();
    testequals();
    testLogic();
    testUpdate();
    testparse();
}