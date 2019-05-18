#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"
#include "String.hpp"

using namespace obotcha;

extern void testArrayList_Boolean();
extern void testArrayList_Integer();
extern void testArrayList_MyData();
extern void testArrayList_String();
extern void testArrayList_Float();
extern void testArrayList_Double();
extern void testArrayList_Long();

int main() {
  testArrayList_Integer();
  testArrayList_MyData();
  testArrayList_String();
  testArrayList_Boolean();
  testArrayList_Float();
  testArrayList_Double();
  testArrayList_Long();
}
