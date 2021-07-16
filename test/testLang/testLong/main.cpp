#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

extern int testtostring();
extern int basetest();
extern int equaltest();
extern int hashcodeTest();
extern int testLongParse();
extern int testLongParseWrong();

int main() {
    basetest();
    equaltest();
    testtostring();
    hashcodeTest();
    testLongParse();
    testLongParseWrong();
    return 0;
}
