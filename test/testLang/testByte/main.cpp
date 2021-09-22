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
extern void updatetest();
extern void equaltest();
extern void testtostring();
extern void testHash();

int main() {
  basetest();
  updatetest();
  equaltest();
  testtostring();
  testHash();
  return 0;
}
