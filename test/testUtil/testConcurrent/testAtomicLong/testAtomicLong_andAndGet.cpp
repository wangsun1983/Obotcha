#include <stdio.h>
#include <unistd.h>

#include "AtomicLong.hpp"
#include "Thread.hpp"

using namespace obotcha;

void testAndAndGet() {
    while(1) {
      AtomicLong Long = createAtomicLong(3);
      long v = Long->andAndGet(2);
      if(v != 2) {
        printf("AtomicLong testAndAndGet test1-------[FAILED],v is %ld \n",v);
        break;
      }
      break;
    }

    printf("AtomicLong testAndAndGet test100-------[OK] \n");
}
