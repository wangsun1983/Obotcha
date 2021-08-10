#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "Integer.hpp"
#include "System.hpp"

using namespace obotcha;

void testBlockingQueueUnlimited() {

    while(1) {
        BlockingQueue<String> list = createBlockingQueue<String>();
        for(int i = 0;i<1024;i++) {
          list->put(createString(i));
        }

        if(list->size() != 1024) {
          printf("BlockingQueue unlimited capacity test1-------[FAIL] \n");
        }

        list->clear();
        if(list->size() != 0) {
          printf("BlockingQueue unlimited capacity test2-------[FAIL] \n");
        }

        break;
    }

    while(1) {
        BlockingQueue<String> list = createBlockingQueue<String>(3);
        Thread t = createThread([&list]{
          usleep(100*1000);
          list->put(createString("a"));
        });
        t->start();
        long time1 = st(System)::currentTimeMillis();
        String str = list->take();
        long time2 = st(System)::currentTimeMillis();
        if((time2 - time1) < 100 || (time2 - time1) > 105) {
          printf("BlockingQueue unlimited capacity-------[FAIL],value is %ld \n",time2 - time1);
          break;
        }

        if(str == nullptr || !str->equals("a")) {
          printf("BlockingQueue unlimited capacity test3-------[FAIL] \n");
          break;
        }
        break;
    }


    printf("BlockingQueue destroy test100-------[OK] \n");
}
