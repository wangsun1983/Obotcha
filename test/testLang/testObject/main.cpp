#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"

using namespace obotcha;

extern int testEqual();
extern int testReferenceCount();
extern int testReferenceArraylist();
extern int testReferenceHashMap();


int main() {
    testEqual();
    testReferenceCount();
    testReferenceArraylist();
    testReferenceHashMap();
}
