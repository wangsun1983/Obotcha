#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingLinkedList.hpp"
#include "Integer.hpp"
#include "System.hpp"
#include "TimeWatcher.hpp"

using namespace obotcha;

void testBlockingLinkedListTryTakeLast() {
    TimeWatcher watcher = createTimeWatcher();

    while(1) {
        BlockingLinkedList<String> list = createBlockingLinkedList<String>(3);
        String v = list->tryTakeLast();
        if(v != nullptr) {
          printf("BlockingLinkedList tryTakeLast test1-------[FAIL] \n");
          break;
        }

        break;
    }

    while(1) {
      BlockingLinkedList<int> list = createBlockingLinkedList<int>();
      bool isException = false;
      try {
        int v = list->tryTakeLast();
      } catch(...) {
        isException = true;
      }

      if(!isException) {
        printf("BlockingLinkedList tryTakeLast test2-------[FAIL] \n");
        break;
      }
      break;
    }

    while(1) {
        BlockingLinkedList<String> list = createBlockingLinkedList<String>(3);
        list->put(createString("a"));
        list->put(createString("b"));

        String v1 = list->tryTakeLast();
        String v2 = list->tryTakeLast();
        String v3 = list->tryTakeLast();
        if(v1 == nullptr || v2 == nullptr || v3 != nullptr) {
          printf("BlockingLinkedList tryTakeLast test3-------[FAIL] \n");
          break;
        }

        if(!v1->equals("b") || !v2->equals("a")) {
          printf("BlockingLinkedList tryTakeLast test4-------[FAIL] \n");
          break;
        }

        break;
    }

    printf("BlockingLinkedList tryTakeLast test100-------[OK] \n");
}
