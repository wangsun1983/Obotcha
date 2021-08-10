#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "Integer.hpp"
#include "System.hpp"

using namespace obotcha;

void testBlockingQueuePeekFirst() {

    while(1) {
        BlockingQueue<String> list = createBlockingQueue<String>(3);
        list->put(createString("a"));
        list->put(createString("b"));
        list->put(createString("c"));

        String v = list->peekFirst();
        if(v == nullptr || !v->equals("a")) {
          printf("BlockingQueue PeekFirst test1-------[FAIL] \n");
          break;
        }

        if(list->size() != 3) {
          printf("BlockingQueue PeekFirst test2-------[FAIL] \n");
          break;
        }
        break;
    }

    while(1) {
      BlockingQueue<String> list = createBlockingQueue<String>(3);

      String v = list->peekFirst();
      if(v != nullptr) {
        printf("BlockingQueue PeekFirst test3-------[FAIL] \n");
        break;
      }

      if(list->size() != 0) {
        printf("BlockingQueue PeekFirst test4-------[FAIL] \n");
        break;
      }
      break;
    }

    printf("BlockingQueue PeekFirst test100-------[OK] \n");
}
