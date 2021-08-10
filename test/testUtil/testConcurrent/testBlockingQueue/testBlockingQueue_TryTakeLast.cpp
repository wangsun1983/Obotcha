#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "Integer.hpp"
#include "System.hpp"
#include "TimeWatcher.hpp"

using namespace obotcha;

void testBlockingQueueTryTakeLast() {
    TimeWatcher watcher = createTimeWatcher();

    while(1) {
        BlockingQueue<String> list = createBlockingQueue<String>(3);
        String v = list->tryTakeLast();
        if(v != nullptr) {
          printf("BlockingQueue tryTakeLast test1-------[FAIL] \n");
          break;
        }

        break;
    }

    while(1) {
      BlockingQueue<int> list = createBlockingQueue<int>();
      bool isException = false;
      try {
        int v = list->tryTakeLast();
      } catch(...) {
        isException = true;
      }

      if(!isException) {
        printf("BlockingQueue tryTakeLast test2-------[FAIL] \n");
        break;
      }
      break;
    }

    while(1) {
        BlockingQueue<String> list = createBlockingQueue<String>(3);
        list->put(createString("a"));
        list->put(createString("b"));

        String v1 = list->tryTakeLast();
        String v2 = list->tryTakeLast();
        String v3 = list->tryTakeLast();
        if(v1 == nullptr || v2 == nullptr || v3 != nullptr) {
          printf("BlockingQueue tryTakeLast test3-------[FAIL] \n");
          break;
        }

        if(!v1->equals("b") || !v2->equals("a")) {
          printf("BlockingQueue tryTakeLast test4-------[FAIL] \n");
          break;
        }

        break;
    }

    printf("BlockingQueue tryTakeLast test100-------[OK] \n");
}
