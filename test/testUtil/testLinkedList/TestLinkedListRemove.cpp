#include <stdio.h>
#include <unistd.h>

#include "LinkedList.hpp"

using namespace obotcha;

void testLinkedListRemove() {

    //case1 string putLast
    while(1) {
        LinkedList<String> mList = createLinkedList<String>();
        mList->putLast(createString("a"));
        mList->putLast(createString("b"));
        mList->putLast(createString("c"));

        int index = mList->remove(createString("b"));
        if(index != 1) {
          printf("LinkedList Remove test1-------[FAILED] \n");
          break;
        }

        index = mList->remove(createString("a"));
        if(index != 0) {
          printf("LinkedList Remove test2-------[FAILED] \n");
          break;
        }

        index = mList->remove(createString("c"));
        if(index != 0) {
          printf("LinkedList Remove test3-------[FAILED] \n");
          break;
        }
        break;
    }

    while(1) {
        LinkedList<String> mList = createLinkedList<String>();
        mList->putLast(createString("a"));
        mList->putLast(createString("b"));
        mList->putLast(createString("c"));

        int index = mList->remove(createString("a"));
        if(index != 0) {
          printf("LinkedList Remove test4-------[FAILED] \n");
          break;
        }

        index = mList->remove(createString("b"));
        if(index != 0) {
          printf("LinkedList Remove test5-------[FAILED] \n");
          break;
        }

        index = mList->remove(createString("c"));
        if(index != 0) {
          printf("LinkedList Remove test6-------[FAILED] \n");
          break;
        }
        break;
    }

    while(1) {
        LinkedList<String> mList = createLinkedList<String>();
        mList->putLast(createString("a"));
        mList->putLast(createString("b"));
        mList->putLast(createString("c"));

        int index = mList->remove(createString("c"));
        if(index != 2) {
          printf("LinkedList Remove test7-------[FAILED] \n");
          break;
        }

        index = mList->remove(createString("b"));
        if(index != 1) {
          printf("LinkedList Remove test8-------[FAILED] \n");
          break;
        }

        index = mList->remove(createString("a"));
        if(index != 0) {
          printf("LinkedList Remove test9-------[FAILED] \n");
          break;
        }
        break;
    }

    while(1) {
        LinkedList<String> mList = createLinkedList<String>();
        mList->putLast(createString("a"));
        mList->putLast(createString("b"));
        mList->putLast(createString("c"));

        int index = mList->remove(createString("d"));
        if(index != -1) {
          printf("LinkedList Remove test1-------[FAILED] \n");
          break;
        }
        break;
    }

    printf("LinkedList Remove test100-------[OK] \n");

}
