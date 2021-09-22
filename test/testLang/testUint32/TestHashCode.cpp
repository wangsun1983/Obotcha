#include <stdio.h>
#include <unistd.h>
#include <cstdio>
#include <sstream>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Uint32.hpp"
#include "StrongPointer.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

void testHash() {
   Uint32 t1 = createUint32(1);
   Uint32 t2 = createUint32(2);
   if(t1->hashcode() == t2->hashcode()) {
    printf("Uint32 hashcode test1-------[FAIL] \n");
    return;
   }

   t1 = createUint32(1);
   t2 = createUint32(1);
   if(t1->hashcode() != t2->hashcode()) {
    printf("Uint32 hashcode test2-------[FAIL] \n");
    return;
   }

   printf("Uint32 hashcode test3-------[OK] \n");
  return;
}
