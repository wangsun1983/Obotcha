#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingLinkedList.hpp"
#include "Integer.hpp"
#include "System.hpp"

using namespace obotcha;

void testBlockingLinkedListToArray() {
    while(1) {
        BlockingLinkedList<String> list = createBlockingLinkedList<String>(3);
        list->put(createString("a"));
        list->put(createString("b"));
        list->put(createString("c"));

        ArrayList<String> ll = list->toArray();
        if(ll->size() != 3 || !ll->get(0)->equals("a")
        || !ll->get(1)->equals("b")
        || !ll->get(2)->equals("c")) {
          printf("BlockingLinkedList toArray test1-------[FAIL] \n");
          break;
        }

        break;
    }

    while(1) {
        BlockingLinkedList<int> list = createBlockingLinkedList<int>(3);
        ArrayList<int> ll = list->toArray();
        if(ll->size() != 0) {
          printf("BlockingLinkedList toArray test2-------[FAIL] \n");
          break;
        }

        break;
    }

    while(1) {
        BlockingLinkedList<int> list = createBlockingLinkedList<int>(128);
        for(int i = 0;i<128;i++) {
          list->putLast(i);
        }
        ArrayList<int> ll = list->toArray();
        auto iterator = ll->getIterator();
        int start = 0;
        while(iterator->hasValue()) {
          if(iterator->getValue() != start) {
            printf("BlockingLinkedList toArray test3-------[FAIL] \n");
            break;
          }
          start++;
          iterator->next();
        }
        break;
    }

    printf("BlockingLinkedList destroy test100-------[OK] \n");
}
