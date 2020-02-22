#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"

using namespace obotcha;
extern int testObjectCompare();

DECLARE_SIMPLE_CLASS(TestClass1) {
public:
    int i;
};

DECLARE_SIMPLE_CLASS(TestClass2) IMPLEMENTS(TestClass1) {
public:
  int j;
};

int main() {
    testObjectCompare();
}
