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
extern int updatetest();
extern int equaltest();
extern int testtostring();

int main() {
  basetest();
  updatetest();
  equaltest();
  testtostring();
}
