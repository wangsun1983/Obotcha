#include <stdio.h>
#include <unistd.h>

#include "AtomicLong.hpp"
#include "Thread.hpp"

using namespace obotcha;

void testGetAndDecrement() {
    while(1) {
        for(int testLoop = 0;testLoop < 1024;testLoop++) {
            AtomicLong value = createAtomicLong(128*64*1024);
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
                printf("AtomicLong GetAndDecrement test1-------[FAILED],value is %ld \n",value->get());
                break;
            }
        }

        break;
    }

    while(1) {
      AtomicLong value = createAtomicLong(5);
      long v = value->getAndDecrement();
      if(v != 5) {
        printf("AtomicLong GetAndDecrement test2-------[FAILED],v is %ld \n",v);
        break;
      }

      if(value->get() != 4) {
        printf("AtomicLong GetAndDecrement test3-------[FAILED],v is %ld \n",value->get());
        break;
      }
      break;
    }

    printf("AtomicLong GetAndDecrement test100-------[OK] \n");
}
