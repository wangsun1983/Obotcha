#include <stdio.h>
#include <unistd.h>

#include "AtomicLong.hpp"
#include "Thread.hpp"

using namespace obotcha;

void testDecrementAndGet() {
    while(1) {
        for(int testLoop = 0;testLoop < 1024;testLoop++) {
            AtomicLong value = createAtomicLong(128*64*1024);
            ArrayList<Thread> list = createArrayList<Thread>();

            for(int i = 0;i < 128;i++) {
                Thread t = createThread([&value] {
                    for(int j = 0;j<64*1024;j++) {
                        value->decrementAndGet();
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
                printf("AtomicLong DecrementAndGet test1-------[FAILED],value is %ld \n",value->get());
                break;
            }
        }

        break;
    }

    while(1) {
      AtomicLong Long = createAtomicLong(5);
      long v = Long->decrementAndGet();
      if(v != 4) {
        printf("AtomicLong DecrementAndGet test2-------[FAILED],v is %ld \n",v);
        break;
      }
      break;
    }

    printf("AtomicLong DecrementAndGet test100-------[OK] \n");
}
