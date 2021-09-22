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

extern void basetest();
extern void operatortest();
extern void dumptest();
extern void testgrow();
extern void testappend();
extern void testsafemode();
extern void testForeach();
extern void testConstruct();
extern void testByteArrayClear();
extern void testByteArrayStruct();
extern void testByteArrayStringConvert();

int main() {
  testByteArrayStringConvert();
  testByteArrayStruct();
  basetest();
  operatortest();
  dumptest();
  testgrow();
  testappend();
  testsafemode();
  testForeach();
  testConstruct();
  testByteArrayClear();
  return 0;
}
