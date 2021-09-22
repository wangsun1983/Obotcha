#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Boolean.hpp"
#include "StrongPointer.hpp"
#include "IllegalArgumentException.hpp"

using namespace obotcha;

extern void basetest();
extern void testequals();
extern void testLogic();
extern void testUpdate();
extern void testparse();

int main() {
    basetest();
    testequals();
    testLogic();
    testUpdate();
    testparse();
    return 0;
}
