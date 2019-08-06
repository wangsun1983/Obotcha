#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "Long.hpp"
#include "StackTrace.hpp"

using namespace obotcha;


void testFunc() {
    st(StackTrace)::dumpStack("test");
}

void testFunc1() {
    testFunc();
}

void testFunc2() {
    testFunc1();
}



int main() {
    testFunc2();

    while(1){}

}
