#include <stdio.h>
#include <unistd.h>

#include "LinkedList.hpp"

using namespace obotcha;

void testLinkedListRemoveAt() {

    //case1 string putLast
    while(1) {
        LinkedList<String> mList = createLinkedList<String>();
        mList->putLast(createString("a"));
        mList->putLast(createString("b"));
        mList->putLast(createString("c"));

        auto str1 = mList->removeAt(1);
        if(!str1->equals("b")) {
          printf("LinkedList RemoveAt test1-------[FAILED] \n");
          break;
        }

        auto str2 = mList->removeAt(1);
        if(!str2->equals("c")) {
          printf("LinkedList RemoveAt test2-------[FAILED] \n");
          break;
        }

        auto str3 = mList->removeAt(0);
        if(!str3->equals("a")) {
          printf("LinkedList RemoveAt test3-------[FAILED] \n");
          break;
        }

        break;
    }

    while(1) {
        LinkedList<String> mList = createLinkedList<String>();
        mList->putLast(createString("a"));
        mList->putLast(createString("b"));
        mList->putLast(createString("c"));

        auto str1 = mList->removeAt(0);
        if(!str1->equals("a")) {
          printf("LinkedList RemoveAt test4-------[FAILED] \n");
          break;
        }

        auto str2 = mList->removeAt(0);
        if(!str2->equals("b")) {
          printf("LinkedList RemoveAt test5-------[FAILED] \n");
          break;
        }

        auto str3 = mList->removeAt(0);
        if(!str3->equals("c")) {
          printf("LinkedList RemoveAt test6-------[FAILED] \n");
          break;
        }

        break;
    }

    while(1) {
        LinkedList<String> mList = createLinkedList<String>();
        mList->putLast(createString("a"));
        mList->putLast(createString("b"));
        mList->putLast(createString("c"));

        String v = mList->removeAt(5);
        if(v != nullptr) {
          printf("LinkedList RemoveAt test7-------[FAILED] \n");
          break;
        }

        break;
    }

    printf("LinkedList RemoveAt test100-------[OK] \n");

}
