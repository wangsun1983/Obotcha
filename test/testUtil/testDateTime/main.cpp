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

extern void tostringtest();
extern void parsetest();
extern void wrongformat();
extern void testToTimeMillis();

int main() {
  testToTimeMillis();
  tostringtest();
  parsetest();
  wrongformat();
}
