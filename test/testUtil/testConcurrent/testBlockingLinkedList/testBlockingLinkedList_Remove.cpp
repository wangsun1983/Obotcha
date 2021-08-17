#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingLinkedList.hpp"
#include "Integer.hpp"
#include "System.hpp"

using namespace obotcha;

void testBlockingLinkedListRemove() {

    while(1) {
        BlockingLinkedList<String> list = createBlockingLinkedList<String>(3);
        list->put(createString("a"));
        list->put(createString("b"));
        list->put(createString("c"));

        list->remove(createString("b"));
        if(list->size() != 2) {
          printf("BlockingLinkedList remove test1-------[FAILED] \n");
          break;
        }

        ArrayList<String> ll = list->toArray();
        if(ll->size() != 2) {
          printf("BlockingLinkedList remove test2-------[FAILED] \n");
          break;
        }

        if(!ll->get(0)->equals("a") || !ll->get(1)->equals("c")) {
          printf("BlockingLinkedList remove test3-------[FAILED] \n");
          break;
        }

        if(list->remove("f") != -1) {
          printf("BlockingLinkedList remove test3_1-------[FAILED] \n");
          break;
        }

        if(list->size() != 2) {
          printf("BlockingLinkedList remove test3_2-------[FAILED] \n");
          break;
        }

        break;
    }

    while(1) {
        BlockingLinkedList<String> list = createBlockingLinkedList<String>(3);
        if(list->remove(createString("a"))!= -1) {
          printf("BlockingLinkedList remove test4-------[FAILED] \n");
          break;
        }

        break;
    }


    printf("BlockingLinkedList remove test100-------[OK] \n");
}
