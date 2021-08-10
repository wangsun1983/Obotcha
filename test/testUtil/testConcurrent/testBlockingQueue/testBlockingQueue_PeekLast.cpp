#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "Integer.hpp"
#include "System.hpp"

using namespace obotcha;

void testBlockingQueuePeekLast() {

    while(1) {
        BlockingQueue<String> list = createBlockingQueue<String>(3);
        list->put(createString("a"));
        list->put(createString("b"));
        list->put(createString("c"));

        String v = list->peekLast();
        if(v == nullptr || !v->equals("c")) {
          printf("BlockingQueue PeekLast test1-------[FAIL] \n");
          break;
        }

        if(list->size() != 3) {
          printf("BlockingQueue PeekLast test2-------[FAIL] \n");
          break;
        }
        break;
    }

    while(1) {
      BlockingQueue<String> list = createBlockingQueue<String>(3);

      String v = list->peekLast();
      if(v != nullptr) {
        printf("BlockingQueue PeekLast test3-------[FAIL] \n");
        break;
      }

      if(list->size() != 0) {
        printf("BlockingQueue PeekLast test4-------[FAIL] \n");
        break;
      }
      break;
    }

    printf("BlockingQueue PeekLast test100-------[OK] \n");
}
