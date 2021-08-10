#include <stdio.h>
#include <unistd.h>

#include "ConcurrentQueue.hpp"

extern void testConcurrentQueue_Size();
extern void testConcurrentQueue_Add();
extern void testConcurrentQueue_Get();

using namespace obotcha;

int main() {
  testConcurrentQueue_Size();
  testConcurrentQueue_Add();
  testConcurrentQueue_Get();
  return 0;
}
