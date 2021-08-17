#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingLinkedList.hpp"
#include "Integer.hpp"
#include "System.hpp"

using namespace obotcha;

void testBlockingLinkedListPeekFirst() {

    while(1) {
        BlockingLinkedList<String> list = createBlockingLinkedList<String>(3);
        list->put(createString("a"));
        list->put(createString("b"));
        list->put(createString("c"));

        String v = list->peekFirst();
        if(v == nullptr || !v->equals("a")) {
          printf("BlockingLinkedList PeekFirst test1-------[FAIL] \n");
          break;
        }

        if(list->size() != 3) {
          printf("BlockingLinkedList PeekFirst test2-------[FAIL] \n");
          break;
        }
        break;
    }

    while(1) {
      BlockingLinkedList<String> list = createBlockingLinkedList<String>(3);

      String v = list->peekFirst();
      if(v != nullptr) {
        printf("BlockingLinkedList PeekFirst test3-------[FAIL] \n");
        break;
      }

      if(list->size() != 0) {
        printf("BlockingLinkedList PeekFirst test4-------[FAIL] \n");
        break;
      }
      break;
    }

    printf("BlockingLinkedList PeekFirst test100-------[OK] \n");
}
