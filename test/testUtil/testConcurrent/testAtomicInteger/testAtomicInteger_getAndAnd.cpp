#include <stdio.h>
#include <unistd.h>

#include "AtomicInteger.hpp"
#include "Thread.hpp"

using namespace obotcha;

void testGetAndAnd() {
    while(1) {
      AtomicInteger integer = createAtomicInteger(7);
      int v = integer->getAndAnd(2);
      if(v != 7) {
        printf("AtomicInteger testGetAndAnd test2-------[FAILED],v is %d \n",v);
        break;
      }

      if(integer->get() != 2) {
        printf("AtomicInteger testGetAndAnd test3-------[FAILED],v is %d \n",integer->get());
        break;
      }
      break;
    }

    printf("AtomicInteger testGetAndAnd test100-------[OK] \n");
}
