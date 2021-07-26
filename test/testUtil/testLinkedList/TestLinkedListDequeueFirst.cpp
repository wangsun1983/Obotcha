#include <stdio.h>
#include <unistd.h>

#include "LinkedList.hpp"

using namespace obotcha;

int testDequeueFirst() {

    //case1
    while(1) {
        LinkedList<String> mList = createLinkedList<String>();
        mList->enQueueLast(createString("a"));
        mList->enQueueLast(createString("b"));
        mList->enQueueLast(createString("c"));

        if(mList->size() != 3) {
            printf("LinkedList Dequeue First test1-------[FAIL] \n");
            break;
        }

        String v1 = mList->deQueueFirst();
        String v2 = mList->deQueueFirst();
        String v3 = mList->deQueueFirst();

        if(!v1->equals("a") ||!v2->equals("b") ||!v3->equals("c")) {
            printf("v1 is %s ,v2 is %s,v3 is %s \n",v1->toChars(),v2->toChars(),v3->toChars());
            printf("LinkedList Dequeue First test2-------[FAIL] \n");
            break;
        }

        if(mList->deQueueFirst() != nullptr) {
            printf("LinkedList Dequeue First test3-------[FAIL] \n");
            break;
        }

        printf("LinkedList Dequeue First test4-------[OK] \n");
        break;
    }

    //case2
    while(1) {
        LinkedList<String> mList = createLinkedList<String>();

        mList->enQueueLast(createString("a"));
        if(mList->size() != 1) {
            printf("LinkedList Dequeue First test5-------[FAIL] \n");
            break;
        }

        String v1 = mList->deQueueFirst();
        if(!v1->equals("a")) {
            printf("v1 is %s \n",v1->toChars());
            printf("LinkedList Dequeue First test6-------[FAIL] \n");
            break;
        }

        if(mList->deQueueFirst() != nullptr) {
            printf("LinkedList Dequeue First test7-------[FAIL] \n");
            break;
        }

        printf("LinkedList Enqueue Last test8-------[OK] \n");
        break;
    }

}
