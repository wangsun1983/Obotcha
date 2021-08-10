#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "Integer.hpp"
#include "System.hpp"

using namespace obotcha;

void testBlockingQueueToArray() {
    while(1) {
        BlockingQueue<String> list = createBlockingQueue<String>(3);
        list->put(createString("a"));
        list->put(createString("b"));
        list->put(createString("c"));

        ArrayList<String> ll = list->toArray();
        if(ll->size() != 3 || !ll->get(0)->equals("a")
        || !ll->get(1)->equals("b")
        || !ll->get(2)->equals("c")) {
          printf("BlockingQueue toArray test1-------[FAIL] \n");
          break;
        }

        break;
    }

    while(1) {
        BlockingQueue<int> list = createBlockingQueue<int>(3);
        ArrayList<int> ll = list->toArray();
        if(ll->size() != 0) {
          printf("BlockingQueue toArray test2-------[FAIL] \n");
          break;
        }

        break;
    }

    while(1) {
        BlockingQueue<int> list = createBlockingQueue<int>(128);
        for(int i = 0;i<128;i++) {
          list->putLast(i);
        }
        ArrayList<int> ll = list->toArray();
        auto iterator = ll->getIterator();
        int start = 0;
        while(iterator->hasValue()) {
          if(iterator->getValue() != start) {
            printf("BlockingQueue toArray test3-------[FAIL] \n");
            break;
          }
          start++;
          iterator->next();
        }
        break;
    }

    printf("BlockingQueue destroy test100-------[OK] \n");
}
