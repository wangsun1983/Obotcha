#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"

using namespace obotcha;
extern int testObjectCompare();
extern int testObjectRef();
extern int testObjectArrayListRef();
extern int testObjectHashmapRef();
extern int testObjectLinkedListRef();

int main() {
    //testObjectCompare();
    //testObjectRef();
    //testObjectArrayListRef();
    //testObjectHashmapRef();
    testObjectLinkedListRef();
}
