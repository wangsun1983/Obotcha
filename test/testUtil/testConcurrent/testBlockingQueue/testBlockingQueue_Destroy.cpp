#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "Integer.hpp"
#include "System.hpp"

using namespace obotcha;

void testBlockingQueueDestroy() {

    while(1) {
        BlockingQueue<String> list = createBlockingQueue<String>(3);
        list->put(createString("a"));
        list->put(createString("b"));
        list->put(createString("c"));

        Thread t = createThread([&list]{
          usleep(100*1000);
          list->destroy();
        });
        t->start();
        long time1 = st(System)::currentTimeMillis();
        list->put(createString("d"));
        long time2 = st(System)::currentTimeMillis();
        if((time2 - time1) < 100 || (time2 - time1) > 105) {
          printf("BlockingQueue destroy test1-------[FAIL],value is %ld \n",time2 - time1);
          break;
        }

        break;
    }

    while(1) {
        BlockingQueue<String> list = createBlockingQueue<String>(3);
        Thread t = createThread([&list]{
          usleep(100*1000);
          list->destroy();
        });
        t->start();
        long time1 = st(System)::currentTimeMillis();
        String str = list->take();
        long time2 = st(System)::currentTimeMillis();
        if((time2 - time1) < 100 || (time2 - time1) > 105) {
          printf("BlockingQueue destroy test2-------[FAIL],value is %ld \n",time2 - time1);
          break;
        }

        if(str != nullptr) {
          printf("BlockingQueue destroy test3-------[FAIL] \n");
          break;
        }
        break;
    }


    printf("BlockingQueue destroy test100-------[OK] \n");
}
