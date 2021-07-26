#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"
#include "String.hpp"

using namespace obotcha;

//extern void testArrayList_Boolean();
extern void testArrayList_Integer();
extern void testArrayList_MyData();
extern void testArrayList_String();

//extern void testArrayList_Float();
//extern void testArrayList_Double();
//extern void testArrayList_Long();
//extern void testArrayList_type_int();

extern int testArrayList_dataType_int();

int main() {
  testArrayList_Integer();
  testArrayList_MyData();
  testArrayList_String();

  testArrayList_dataType_int();
  //testArrayList_Boolean(); no need to test
  //testArrayList_Float(); no need to test
  //testArrayList_Double(); no need to test
  //testArrayList_Long(); no need to test
  //testArrayList_type_int(); no need to test
}
