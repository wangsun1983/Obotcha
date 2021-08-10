#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "Integer.hpp"
#include "System.hpp"

using namespace obotcha;

void testBlockingQueuePutLast() {

    while(1) {
        BlockingQueue<String> list = createBlockingQueue<String>(3);
        list->putLast(createString("a"));
        list->putLast(createString("b"));
        list->putLast(createString("c"));

        Thread t = createThread([&list]{
          usleep(100*1000);
          list->takeLast();
        });
        t->start();

        long time1 = st(System)::currentTimeMillis();
        list->putLast("d");
        long time2 = st(System)::currentTimeMillis();

        if((time2 - time1) < 100 || (time2 - time1) > 105) {
          printf("BlockingQueue PutLast test1-------[FAIL],value is %ld \n",time2 - time1);
          break;
        }

        ArrayList<String> result = createArrayList<String>();
        result->add(createString("a"));
        result->add(createString("b"));
        result->add(createString("d"));
        auto iterator = result->getIterator();
        while(iterator->hasValue()) {
          auto v = iterator->getValue();
          auto v2 = list->takeFirst();
          if(!v->equals(v2)) {
            printf("BlockingQueue PutLast test2-------[FAIL],v is %s,v2 is %s \n",v->toChars(),v2->toChars());
            break;
          }
          iterator->next();
        }

        break;
    }


    printf("BlockingQueue PutLast test100-------[OK] \n");
}
