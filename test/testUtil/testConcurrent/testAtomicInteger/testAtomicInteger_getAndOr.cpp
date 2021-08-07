#include <stdio.h>
#include <unistd.h>

#include "AtomicInteger.hpp"
#include "Thread.hpp"

using namespace obotcha;

void testGetAndOr() {
    while(1) {
      AtomicInteger integer = createAtomicInteger(1);
      int v = integer->getAndOr(4);
      if(v != 1) {
        printf("AtomicInteger testGetAndOr test2-------[FAILED],v is %d \n",v);
        break;
      }

      if(integer->get() != 5) {
        printf("AtomicInteger testGetAndOr test3-------[FAILED],v is %d \n",integer->get());
        break;
      }
      break;
    }

    printf("AtomicInteger testGetAndOr test100-------[OK] \n");
}
