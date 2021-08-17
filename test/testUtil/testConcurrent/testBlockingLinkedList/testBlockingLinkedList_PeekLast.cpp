#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingLinkedList.hpp"
#include "Integer.hpp"
#include "System.hpp"

using namespace obotcha;

void testBlockingLinkedListPeekLast() {

    while(1) {
        BlockingLinkedList<String> list = createBlockingLinkedList<String>(3);
        list->put(createString("a"));
        list->put(createString("b"));
        list->put(createString("c"));

        String v = list->peekLast();
        if(v == nullptr || !v->equals("c")) {
          printf("BlockingLinkedList PeekLast test1-------[FAIL] \n");
          break;
        }

        if(list->size() != 3) {
          printf("BlockingLinkedList PeekLast test2-------[FAIL] \n");
          break;
        }
        break;
    }

    while(1) {
      BlockingLinkedList<String> list = createBlockingLinkedList<String>(3);

      String v = list->peekLast();
      if(v != nullptr) {
        printf("BlockingLinkedList PeekLast test3-------[FAIL] \n");
        break;
      }

      if(list->size() != 0) {
        printf("BlockingLinkedList PeekLast test4-------[FAIL] \n");
        break;
      }
      break;
    }

    printf("BlockingLinkedList PeekLast test100-------[OK] \n");
}
