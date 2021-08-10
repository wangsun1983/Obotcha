#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "Integer.hpp"
#include "System.hpp"
#include "TimeWatcher.hpp"

using namespace obotcha;

void testBlockingQueueTryTakeFirst() {
    TimeWatcher watcher = createTimeWatcher();

    while(1) {
        BlockingQueue<String> list = createBlockingQueue<String>(3);
        String v = list->tryTakeFirst();
        if(v != nullptr) {
          printf("BlockingQueue tryTakeFirst test1-------[FAIL] \n");
          break;
        }

        break;
    }

    while(1) {
      BlockingQueue<int> list = createBlockingQueue<int>();
      bool isException = false;
      try {
        int v = list->tryTakeFirst();
      } catch(...) {
        isException = true;
      }

      if(!isException) {
        printf("BlockingQueue tryTakeFirst test2-------[FAIL] \n");
        break;
      }
      break;
    }

    while(1) {
        BlockingQueue<String> list = createBlockingQueue<String>(3);
        list->put(createString("a"));
        list->put(createString("b"));

        String v1 = list->tryTakeFirst();
        String v2 = list->tryTakeFirst();
        String v3 = list->tryTakeFirst();
        if(v1 == nullptr || v2 == nullptr || v3 != nullptr) {
          printf("BlockingQueue tryTakeFirst test3-------[FAIL] \n");
          break;
        }

        if(!v1->equals("a") || !v2->equals("b")) {
          printf("BlockingQueue tryTakeFirst test4-------[FAIL] \n");
          break;
        }

        break;
    }

    printf("BlockingQueue tryTakeFirst test100-------[OK] \n");
}
