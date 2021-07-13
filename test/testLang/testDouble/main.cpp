#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Double.hpp"
#include "StrongPointer.hpp"

using namespace obotcha;

extern int basetest();
extern int equaltest();
extern int testToString();
extern int hashtest();

int main() {
  basetest();
  equaltest();
  testToString();
  printf("start hash test \n");
  hashtest();
}
