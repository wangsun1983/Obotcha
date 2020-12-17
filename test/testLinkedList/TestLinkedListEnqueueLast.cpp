#include <stdio.h>
#include <unistd.h>

#include "LinkedList.hpp"

using namespace obotcha;

int testEnqueueLast() {

    //case1
    while(1) {
        LinkedList<String> mList = createLinkedList<String>();
        mList->enQueueLast(createString("a"));
        mList->enQueueLast(createString("b"));
        mList->enQueueLast(createString("c"));

        if(mList->size() != 3) {
            printf("LinkedList Enqueue Last test1-------[FAIL] \n");
            break;
        }

        String v1 = mList->deQueueLast();
        String v2 = mList->deQueueLast();
        String v3 = mList->deQueueLast();

        if(!v1->equals("c") ||!v2->equals("b") ||!v3->equals("a")) {
            printf("v1 is %s ,v2 is %s,v3 is %s \n",v1->toChars(),v2->toChars(),v3->toChars());
            printf("LinkedList Dequeue Last test2-------[FAIL] \n");
            break;
        }

        if(mList->deQueueLast() != nullptr) {
            printf("LinkedList Dequeue Last test3-------[FAIL] \n");
            break;
        }

        printf("LinkedList Dequeue Last test4-------[OK] \n");
        break;
    }

    //case2
    while(1) {
        LinkedList<String> mList = createLinkedList<String>();
        if(mList->deQueueLast() != nullptr) {
          printf("LinkedList Dequeue Last test5-------[FAIL] \n");
          break;
        }
        printf("LinkedList Dequeue Last test6-------[OK] \n");
        break;
    }

}
