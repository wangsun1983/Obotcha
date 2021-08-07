#include <stdio.h>
#include <unistd.h>

#include "AtomicInteger.hpp"
#include "Thread.hpp"

using namespace obotcha;

void testGetAndAdd() {
    while(1) {
        for(int testLoop = 0;testLoop < 1024;testLoop++) {
            AtomicInteger value = createAtomicInteger(0);
            ArrayList<Thread> list = createArrayList<Thread>();

            for(int i = 0;i < 64;i++) {
                Thread t = createThread([&value] {
                    for(int j = 0;j<64*1024;j++) {
                        value->getAndAdd(2);
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

            if(value->get() != 64*64*1024*2) {
                printf("AtomicInteger GetAndAdd test1-------[FAILED],value is %d \n",value->get());
                break;
            }
        }

        break;
    }

    while(1) {
      AtomicInteger integer = createAtomicInteger(3);
      int v = integer->getAndAdd(2);
      if(v != 3) {
        printf("AtomicInteger GetAndAdd test2-------[FAILED],v is %d \n",v);
        break;
      }

      if(integer->get() != 5) {
        printf("AtomicInteger GetAndAdd test3-------[FAILED],v is %d \n",integer->get());
        break;
      }

      break;
    }
    printf("AtomicInteger AddAndGet test100-------[OK] \n");
}
