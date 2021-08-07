#include <stdio.h>
#include <unistd.h>

#include "AtomicInteger.hpp"
#include "Thread.hpp"

using namespace obotcha;

void testOrAndGet() {
    while(1) {
      AtomicInteger integer = createAtomicInteger(1);
      int v = integer->orAndGet(2);
      if(v != 3) {
        printf("AtomicInteger testOrAndGet test1-------[FAILED],v is %d \n",v);
        break;
      }
      break;
    }

    printf("AtomicInteger testOrAndGet test100-------[OK] \n");
}
