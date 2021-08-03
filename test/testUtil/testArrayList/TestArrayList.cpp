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
extern void testArrayList_Add();
extern void testArrayList_Remove();
extern int testArrayList_dataType_int();
extern void testArrayList_Construct();
extern void testArrayList_InsertLast();

int main() {
  testArrayList_Integer();
  testArrayList_MyData();
  testArrayList_String();
  testArrayList_dataType_int();
  testArrayList_Add();
  testArrayList_Remove();
  testArrayList_Boolean();
  testArrayList_dataType_int();
  testArrayList_Construct();
  testArrayList_InsertLast();
}
