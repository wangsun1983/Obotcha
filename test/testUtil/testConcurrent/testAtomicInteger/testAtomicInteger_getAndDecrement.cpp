#include <stdio.h>
#include <unistd.h>

#include "AtomicInteger.hpp"
#include "Thread.hpp"

using namespace obotcha;

void testGetAndDecrement() {
    while(1) {
        for(int testLoop = 0;testLoop < 1024;testLoop++) {
            AtomicInteger value = createAtomicInteger(128*64*1024);
            ArrayList<Thread> list = createArrayList<Thread>();

            for(int i = 0;i < 128;i++) {
                Thread t = createThread([&value] {
                    for(int j = 0;j<64*1024;j++) {
                        value->getAndDecrement();
                    }
                });
                list->add(t);
                t->start();
            }

            auto iterator = list->getIterator();
            while(iterator->hasValue()) {
               auto t = iterator->getValue();
               t->join();
               iterator->next();
            }

            if(value->get() != 0) {
                printf("AtomicInteger GetAndDecrement test1-------[FAILED],value is %d \n",value->get());
                break;
            }
        }

        break;
    }

    while(1) {
      AtomicInteger integer = createAtomicInteger(5);
      int v = integer->getAndDecrement();
      if(v != 5) {
        printf("AtomicInteger GetAndDecrement test2-------[FAILED],v is %d \n",v);
        break;
      }

      if(integer->get() != 4) {
        printf("AtomicInteger GetAndDecrement test3-------[FAILED],v is %d \n",v);
        break;
      }
      break;
    }

    printf("AtomicInteger GetAndDecrement test100-------[OK] \n");
}
