#include <stdio.h>
#include <unistd.h>

#include "AtomicLong.hpp"
#include "Thread.hpp"

using namespace obotcha;

void testGetAndAdd() {
    while(1) {
        for(int testLoop = 0;testLoop < 1024;testLoop++) {
            AtomicLong value = createAtomicLong(0);
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
                printf("AtomicLong GetAndAdd test1-------[FAILED],value is %ld \n",value->get());
                break;
            }
        }

        break;
    }

    while(1) {
      AtomicLong value = createAtomicLong(3);
      long v = value->getAndAdd(2);
      if(v != 3) {
        printf("AtomicLong GetAndAdd test2-------[FAILED],v is %ld \n",v);
        break;
      }

      if(value->get() != 5) {
        printf("AtomicLong GetAndAdd test3-------[FAILED],v is %ld \n",value->get());
        break;
      }

      break;
    }
    printf("AtomicLong AddAndGet test100-------[OK] \n");
}
