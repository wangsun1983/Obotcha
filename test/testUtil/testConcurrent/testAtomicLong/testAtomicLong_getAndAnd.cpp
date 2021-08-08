#include <stdio.h>
#include <unistd.h>

#include "AtomicLong.hpp"
#include "Thread.hpp"

using namespace obotcha;

void testGetAndAnd() {
    while(1) {
      AtomicLong value = createAtomicLong(7);
      long v = value->getAndAnd(2);
      if(v != 7) {
        printf("AtomicLong testGetAndAnd test2-------[FAILED],v is %ld \n",v);
        break;
      }

      if(value->get() != 2) {
        printf("AtomicLong testGetAndAnd test3-------[FAILED],v is %ld \n",value->get());
        break;
      }
      break;
    }

    printf("AtomicLong testGetAndAnd test100-------[OK] \n");
}
