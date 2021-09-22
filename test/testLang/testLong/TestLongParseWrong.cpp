#include <stdio.h>
#include <unistd.h>
#include <cstdio>
#include <sstream>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Long.hpp"
#include "StrongPointer.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

void testLongParseWrong() {
  while(1) {
   Long v1 = st(Long)::parseDecLong("xd");
   if(v1 != nullptr) {
    printf("Long testLongParseWrong test1-------[FAIL] \n");
    break;
   }

   v1 = st(Long)::parseHexLong("xd");
   if(v1 != nullptr) {
    printf("Long testLongParseWrong test2-------[FAIL] \n");
    break;
   }

   v1 = st(Long)::parseOctLong("xd");
   if(v1 != nullptr) {
    printf("Long testLongParseWrong test3-------[FAIL] \n");
    break;
   }

   v1 = st(Long)::parseBinaryLong("111d");
   if(v1 != nullptr) {
    printf("Long testLongParseWrong test4-------[FAIL] \n");
    break;
   }

   printf("Long testLongParseWrong test5-------[OK] \n");
   break;
  }
}
