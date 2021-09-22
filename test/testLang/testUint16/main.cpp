#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

extern void testtostring();
extern void basetest();
extern void equaltest();
extern void testHash();
extern void TestParseException();

int main() {
    basetest();
    equaltest();
    testtostring();
    testHash();
    TestParseException();
    return 0;
}
