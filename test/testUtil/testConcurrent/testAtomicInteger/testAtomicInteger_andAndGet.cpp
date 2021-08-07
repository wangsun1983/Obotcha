#include <stdio.h>
#include <unistd.h>

#include "AtomicInteger.hpp"
#include "Thread.hpp"

using namespace obotcha;

void testAndAndGet() {
    while(1) {
      AtomicInteger integer = createAtomicInteger(3);
      int v = integer->andAndGet(2);
      if(v != 2) {
        printf("AtomicInteger testAndAndGet test1-------[FAILED],v is %d \n",v);
        break;
      }
      break;
    }

    printf("AtomicInteger testAndAndGet test100-------[OK] \n");
}
