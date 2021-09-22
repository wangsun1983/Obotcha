#include <stdio.h>
#include <unistd.h>
#include <cstdio>
#include <sstream>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Uint16.hpp"
#include "StrongPointer.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

void testHash() {
   Uint16 t1 = createUint16(1);
   Uint16 t2 = createUint16(2);
   if(t1->hashcode() == t2->hashcode()) {
    printf("Uint16 hashcode test1-------[FAIL] \n");
    return;
   }

   t1 = createUint16(1);
   t2 = createUint16(1);
   if(t1->hashcode() != t2->hashcode()) {
    printf("Uint16 hashcode test2-------[FAIL] \n");
    return;
   }

   printf("Uint16 hashcode test3-------[OK] \n");
   return;
}
