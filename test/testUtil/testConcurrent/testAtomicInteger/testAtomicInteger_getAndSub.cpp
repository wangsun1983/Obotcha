#include <stdio.h>
#include <unistd.h>

#include "AtomicInteger.hpp"
#include "Thread.hpp"

using namespace obotcha;

void testGetAndSub() {
    while(1) {
        for(int testLoop = 0;testLoop < 1024;testLoop++) {
            AtomicInteger value = createAtomicInteger(64*64*1024);
            ArrayList<Thread> list = createArrayList<Thread>();

            for(int i = 0;i < 32;i++) {
                Thread t = createThread([&value] {
                    for(int j = 0;j<64*1024;j++) {
                        value->getAndSub(2);
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
                printf("AtomicInteger GetAndSub test1-------[FAILED],value is %d \n",value->get());
                break;
            }
        }

        break;
    }

    while(1) {
      AtomicInteger integer = createAtomicInteger(5);
      int v = integer->getAndSub(2);
      if(v != 5) {
        printf("AtomicInteger GetAndSub test2-------[FAILED],v is %d \n",v);
        break;
      }

      if(integer->get() != 3) {
        printf("AtomicInteger GetAndSub test3-------[FAILED],v is %d \n",integer->get());
        break;
      }
      break;
    }

    printf("AtomicInteger SubAndGet test100-------[OK] \n");
}
