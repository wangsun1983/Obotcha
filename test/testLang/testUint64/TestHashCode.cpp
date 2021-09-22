#include <stdio.h>
#include <unistd.h>
#include <cstdio>
#include <sstream>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Uint64.hpp"
#include "StrongPointer.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

void testHash() {
   Uint64 t1 = createUint64(1);
   Uint64 t2 = createUint64(2);
   if(t1->hashcode() == t2->hashcode()) {
    printf("Uint64 hashcode test1-------[FAIL] \n");
    return;
   }

   t1 = createUint64(1);
   t2 = createUint64(1);
   if(t1->hashcode() != t2->hashcode()) {
    printf("Uint64 hashcode test2-------[FAIL] \n");
    return;
   }

   printf("Uint64 hashcode test3-------[OK] \n");
  return;
}
