#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingLinkedList.hpp"
#include "Integer.hpp"
#include "System.hpp"
#include "TimeWatcher.hpp"

using namespace obotcha;

void testBlockingLinkedListTryTakeFirst() {
    TimeWatcher watcher = createTimeWatcher();

    while(1) {
        BlockingLinkedList<String> list = createBlockingLinkedList<String>(3);
        String v = list->tryTakeFirst();
        if(v != nullptr) {
          printf("BlockingLinkedList tryTakeFirst test1-------[FAIL] \n");
          break;
        }

        break;
    }

    while(1) {
      BlockingLinkedList<int> list = createBlockingLinkedList<int>();
      bool isException = false;
      try {
        int v = list->tryTakeFirst();
      } catch(...) {
        isException = true;
      }

      if(!isException) {
        printf("BlockingLinkedList tryTakeFirst test2-------[FAIL] \n");
        break;
      }
      break;
    }

    while(1) {
        BlockingLinkedList<String> list = createBlockingLinkedList<String>(3);
        list->put(createString("a"));
        list->put(createString("b"));

        String v1 = list->tryTakeFirst();
        String v2 = list->tryTakeFirst();
        String v3 = list->tryTakeFirst();
        if(v1 == nullptr || v2 == nullptr || v3 != nullptr) {
          printf("BlockingLinkedList tryTakeFirst test3-------[FAIL] \n");
          break;
        }

        if(!v1->equals("a") || !v2->equals("b")) {
          printf("BlockingLinkedList tryTakeFirst test4-------[FAIL] \n");
          break;
        }

        break;
    }

    printf("BlockingLinkedList tryTakeFirst test100-------[OK] \n");
}
