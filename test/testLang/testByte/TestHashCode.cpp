#include <stdio.h>
#include <unistd.h>
#include <cstdio>
#include <sstream>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Byte.hpp"
#include "StrongPointer.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

int testHash() {
   Byte t1 = createByte(1);
   Byte t2 = createByte(2);
   if(t1->hashcode() == t2->hashcode()) {
    printf("Byte hashcode test1-------[FAIL] \n");
    return 0;
   }

   t1 = createByte(1);
   t2 = createByte(1);
   if(t1->hashcode() != t2->hashcode()) {
    printf("Byte hashcode test2-------[FAIL] \n");
    return 0;
   }

   printf("Byte hashcode test3-------[OK] \n");
  return 0;
}
