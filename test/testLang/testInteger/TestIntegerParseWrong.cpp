#include <stdio.h>
#include <unistd.h>
#include <cstdio>
#include <sstream>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

void testIntegerParseWrong() {
  while(1) {
   Integer v1 = st(Integer)::parseDecInt("xd");
   if(v1 != nullptr) {
    printf("Integer testIntegerParseWrong test1-------[FAIL] \n");
    break;
   }

   v1 = st(Integer)::parseHexInt("xd");
   if(v1 != nullptr) {
    printf("Integer testIntegerParseWrong test2-------[FAIL] \n");
    break;
   }

   v1 = st(Integer)::parseOctInt("xd");
   if(v1 != nullptr) {
    printf("Integer testIntegerParseWrong test3-------[FAIL] \n");
    break;
   }

   v1 = st(Integer)::parseBinaryInt("111d");
   if(v1 != nullptr) {
    printf("Integer testIntegerParseWrong test4-------[FAIL] \n");
    break;
   }

   printf("Integer testIntegerParseWrong test5-------[OK] \n");
   break;
  }
}
