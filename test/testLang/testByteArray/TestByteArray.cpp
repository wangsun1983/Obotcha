#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "ByteArray.hpp"
#include "StrongPointer.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"

using namespace obotcha;

extern int basetest();
extern int operatortest();
extern int dumptest();
extern int testgrow();
extern int testappend();
extern int testsafemode();
extern int testForeach();
extern int testConstruct();
extern int testByteArrayClear();

int main() {

  basetest();
  operatortest();
  dumptest();
  testgrow();
  testappend();
  testsafemode();
  testForeach();
  testConstruct();
  testByteArrayClear();
}
