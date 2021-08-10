#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "Integer.hpp"
#include "System.hpp"
#include "TimeWatcher.hpp"

using namespace obotcha;

void testBlockingQueueTakeFirst() {
    TimeWatcher watcher = createTimeWatcher();

    while(1) {
        BlockingQueue<String> list = createBlockingQueue<String>(3);
        list->put(createString("a"));
        list->put(createString("b"));
        list->put(createString("c"));

        String v = list->takeFirst();
        if(v == nullptr || !v->equals("a")) {
          printf("BlockingQueue takeFirst test1-------[FAIL] \n");
          break;
        }

        if(list->size() != 2) {
          printf("BlockingQueue takeFirst test2-------[FAIL] \n");
          break;
        }
        break;
    }

    while(1) {
      BlockingQueue<String> list = createBlockingQueue<String>(3);
      Thread t = createThread([&list] {
        usleep(100*1000);
        list->put(createString("a"));
      });
      t->start();

      watcher->start();
      String v = list->takeFirst();
      long interval = watcher->stop();
      if(v == nullptr || !v->equals("a")) {
        printf("BlockingQueue takeFirst test3-------[FAIL] \n");
        break;
      }

      if(interval < 100 || interval > 105) {
        printf("BlockingQueue takeFirst test4-------[FAIL] \n");
        break;
      }

      if(list->size() != 0) {
        printf("BlockingQueue takeFirst test5-------[FAIL] \n");
        break;
      }
      break;
    }

    printf("BlockingQueue takeFirst test100-------[OK] \n");
}
