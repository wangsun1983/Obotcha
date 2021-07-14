#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "InitializeException.hpp"
#include "Integer.hpp"

using namespace obotcha;

extern int testtostring();
extern int basetest();
extern int equaltest();
extern int testIntegerParse();
extern int testIntegerParseWrong();

int main() {
    basetest();
    equaltest();
    testtostring();
    testIntegerParse();
    testIntegerParseWrong();
}
