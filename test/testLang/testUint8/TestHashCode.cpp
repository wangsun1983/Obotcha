#include <stdio.h>
#include <unistd.h>
#include <cstdio>
#include <sstream>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Uint8.hpp"
#include "StrongPointer.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

int testHash() {
   Uint8 t1 = createUint8(1);
   Uint8 t2 = createUint8(2);
   if(t1->hashcode() == t2->hashcode()) {
    printf("Uint8 hashcode test1-------[FAIL] \n");
    return 0;
   }

   t1 = createUint8(1);
   t2 = createUint8(1);
   if(t1->hashcode() != t2->hashcode()) {
    printf("Uint8 hashcode test2-------[FAIL] \n");
    return 0;
   }

   printf("Uint8 hashcode test3-------[OK] \n");
  return 0;
}
