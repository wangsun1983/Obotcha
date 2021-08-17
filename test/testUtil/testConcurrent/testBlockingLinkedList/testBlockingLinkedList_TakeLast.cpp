#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingLinkedList.hpp"
#include "Integer.hpp"
#include "System.hpp"
#include "TimeWatcher.hpp"

using namespace obotcha;

void testBlockingLinkedListTakeLast() {
    TimeWatcher watcher = createTimeWatcher();

    while(1) {
        BlockingLinkedList<String> list = createBlockingLinkedList<String>(3);
        list->put(createString("a"));
        list->put(createString("b"));
        list->put(createString("c"));

        String v = list->takeLast();
        if(v == nullptr || !v->equals("c")) {
          printf("BlockingLinkedList TakeLast test1-------[FAIL] \n");
          break;
        }

        if(list->size() != 2) {
          printf("BlockingLinkedList TakeLast test2-------[FAIL] \n");
          break;
        }
        break;
    }

    while(1) {
      BlockingLinkedList<String> list = createBlockingLinkedList<String>(3);
      Thread t = createThread([&list] {
        usleep(100*1000);
        list->put(createString("a"));
      });
      t->start();

      watcher->start();
      String v = list->takeLast();
      long interval = watcher->stop();
      if(v == nullptr || !v->equals("a")) {
        printf("BlockingLinkedList TakeLast test3-------[FAIL] \n");
        break;
      }

      if(interval < 100 || interval > 105) {
        printf("BlockingLinkedList TakeLast test4-------[FAIL] \n");
        break;
      }

      if(list->size() != 0) {
        printf("BlockingLinkedList TakeLast test5-------[FAIL] \n");
        break;
      }
      break;
    }

    printf("BlockingLinkedList TakeLast test100-------[OK] \n");
}
