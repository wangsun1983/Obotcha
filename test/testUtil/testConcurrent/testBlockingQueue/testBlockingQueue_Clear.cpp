#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "Integer.hpp"
#include "System.hpp"

using namespace obotcha;

void testBlockingQueueClear() {

    while(1) {
        BlockingQueue<String> list = createBlockingQueue<String>(3);
        list->put(createString("a"));
        list->put(createString("b"));
        list->put(createString("c"));

        Thread t = createThread([&list]{
          usleep(100*1000);
          list->clear();
        });
        t->start();
        long time1 = st(System)::currentTimeMillis();
        list->put(createString("d"));
        long time2 = st(System)::currentTimeMillis();
        if((time2 - time1) < 100 || (time2 - time1) > 105) {
          printf("BlockingQueue clear test1-------[FAIL],value is %ld \n",time2 - time1);
          break;
        }

        if(list->size() != 0) {
          printf("BlockingQueue clear test2-------[FAIL] \n");
          break;
        }

        break;
    }

    printf("BlockingQueue destroy test100-------[OK] \n");
}
