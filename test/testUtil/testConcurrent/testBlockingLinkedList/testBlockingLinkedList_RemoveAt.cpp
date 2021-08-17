#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingLinkedList.hpp"
#include "Integer.hpp"
#include "System.hpp"

using namespace obotcha;

void testBlockingLinkedListRemoveAt() {

    while(1) {
        BlockingLinkedList<String> list = createBlockingLinkedList<String>(3);
        list->put(createString("a"));
        list->put(createString("b"));
        list->put(createString("c"));

        String v = list->removeAt(1);
        if(v == nullptr || !v->equals("b")) {
          printf("BlockingLinkedList removeAt test1-------[FAILED] \n");
          break;
        }

        if(list->size() != 2) {
          printf("BlockingLinkedList removeAt test2-------[FAILED] \n");
          break;
        }
        break;
    }

    while(1) {
        BlockingLinkedList<String> list = createBlockingLinkedList<String>(3);
        bool isException = false;
        try {
          String v = list->removeAt(1);
        } catch(...) {
          isException = true;
        }

        if(!isException) {
          printf("BlockingLinkedList removeAt test3-------[FAILED] \n");
          break;
        }

        break;
    }

    while(1) {
        BlockingLinkedList<String> list = createBlockingLinkedList<String>(3);
        bool isException = false;
        try {
          String v = list->removeAt(0);
        } catch(...) {
          isException = true;
        }

        if(!isException) {
          printf("BlockingLinkedList removeAt test4-------[FAILED] \n");
          break;
        }

        break;
    }

    while(1) {
        BlockingLinkedList<String> list = createBlockingLinkedList<String>(3);
        list->put(createString("a"));
        bool isException = false;
        try {
          String v = list->removeAt(2);
        } catch(...) {
          isException = true;
        }

        if(!isException) {
          printf("BlockingLinkedList removeAt test5-------[FAILED] \n");
          break;
        }

        break;
    }

    printf("BlockingLinkedList removeAt test100-------[OK] \n");
}
