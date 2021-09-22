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
extern void TestParseException();
extern void testHash();

int main() {
    basetest();
    equaltest();
    testtostring();
    TestParseException();
    testHash();
    return 0;
}
