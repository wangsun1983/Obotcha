#include <stdio.h>
#include <unistd.h>

#include "AtomicLong.hpp"
#include "Thread.hpp"

using namespace obotcha;

void testOrAndGet() {
    while(1) {
      AtomicLong value = createAtomicLong(1);
      long v = value->orAndGet(2);
      if(v != 3) {
        printf("AtomicLong testOrAndGet test1-------[FAILED],v is %ld \n",v);
        break;
      }
      break;
    }

    printf("AtomicLong testOrAndGet test100-------[OK] \n");
}
