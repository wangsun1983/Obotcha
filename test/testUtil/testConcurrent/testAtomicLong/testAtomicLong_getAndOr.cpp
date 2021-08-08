#include <stdio.h>
#include <unistd.h>

#include "AtomicLong.hpp"
#include "Thread.hpp"

using namespace obotcha;

void testGetAndOr() {
    while(1) {
      AtomicLong value = createAtomicLong(1);
      long v = value->getAndOr(4);
      if(v != 1) {
        printf("AtomicLong testGetAndOr test2-------[FAILED],v is %ld \n",v);
        break;
      }

      if(value->get() != 5) {
        printf("AtomicLong testGetAndOr test3-------[FAILED],v is %ld \n",value->get());
        break;
      }
      break;
    }

    printf("AtomicLong testGetAndOr test100-------[OK] \n");
}
