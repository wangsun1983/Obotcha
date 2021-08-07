#include <stdio.h>
#include <unistd.h>

#include "AtomicInteger.hpp"
#include "Thread.hpp"

using namespace obotcha;

void testAddAndGet() {
    while(1) {
        for(int testLoop = 0;testLoop < 1024;testLoop++) {
            AtomicInteger value = createAtomicInteger(0);
            ArrayList<Thread> list = createArrayList<Thread>();

            for(int i = 0;i < 64;i++) {
                Thread t = createThread([&value] {
                    for(int j = 0;j<64*1024;j++) {
                        value->addAndGet(2);
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
                printf("AtomicInteger AddAndGet test1-------[FAILED],value is %d \n",value->get());
                break;
            }
        }

        break;
    }

    while(1) {
      AtomicInteger integer = createAtomicInteger(3);
      int v = integer->addAndGet(2);
      if(v != 5) {
        printf("AtomicInteger AddAndGet test2-------[FAILED],v is %d \n",v);
        break;
      }

      break;
    }
    printf("AtomicInteger AddAndGet test100-------[OK] \n");
}
