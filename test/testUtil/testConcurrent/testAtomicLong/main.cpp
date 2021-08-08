#include <stdio.h>
#include <unistd.h>

#include "Object.hpp"

using namespace obotcha;

extern void testIncrementAndGet();
extern void testDecrementAndGet();
extern void testAddAndGet();
extern void testSubAndGet();
extern void testAndAndGet();
extern void testOrAndGet();

extern void testGetAndDecrement();
extern void testGetAndIncrement();
extern void testGetAndAdd();
extern void testGetAndSub();
extern void testGetAndAnd();
extern void testGetAndOr();

int main() {
  testIncrementAndGet();
  testDecrementAndGet();
  testAddAndGet();
  testSubAndGet();
  testAndAndGet();
  testOrAndGet();

  testGetAndDecrement();
  testGetAndAdd();
  testGetAndIncrement();
  testGetAndSub();
  testGetAndAnd();
  testGetAndOr();

  return 0;
}
