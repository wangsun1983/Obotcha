#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Double.hpp"
#include "StrongPointer.hpp"

using namespace obotcha;

extern int basetest();
extern int equaltest();

int main() {
  basetest();

  equaltest();
}
