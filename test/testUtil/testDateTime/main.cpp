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

extern int tostringtest();
extern int parsetest();
extern int wrongformat();

int main() {
  tostringtest();
  parsetest();
  wrongformat();
}
