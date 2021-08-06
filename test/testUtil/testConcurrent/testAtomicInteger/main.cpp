#include <stdio.h>
#include <unistd.h>

#include "Object.hpp"

using namespace obotcha;

extern void testIncrementAndGet();

int main() {
  testIncrementAndGet();

  return 0;  
}
