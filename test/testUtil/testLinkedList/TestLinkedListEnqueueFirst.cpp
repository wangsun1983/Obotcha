#include <stdio.h>
#include <unistd.h>

#include "LinkedList.hpp"

using namespace obotcha;

int testPutFirst() {

    //case1
    while(1) {
        LinkedList<String> mList = createLinkedList<String>();
        std::vector<std::string> list;
        list.push_back("a");
        list.push_back("b");
        list.push_back("c");

        mList->putFirst(createString("a"));
        mList->putFirst(createString("b"));
        mList->putFirst(createString("c"));

        if(mList->size() != 3) {
            printf("LinkedList Enqueue First test1-------[FAIL] \n");
            break;
        }

        String v1 = mList->at(0);
        String v2 = mList->at(1);
        String v3 = mList->at(2);

        if(!v1->equals("c") ||!v2->equals("b") ||!v3->equals("a")) {
            printf("v1 is %s ,v2 is %s,v3 is %s \n",v1->toChars(),v2->toChars(),v3->toChars());
            printf("LinkedList Enqueue First test2-------[FAIL] \n");
            break;
        }
        printf("LinkedList Enqueue First test3-------[OK] \n");
        break;
    }

    //case2
    while(1) {
        LinkedList<String> mList = createLinkedList<String>();

        mList->putFirst(createString("a"));
        if(mList->size() != 1) {
            printf("LinkedList Enqueue First test4-------[FAIL] \n");
            break;
        }

        String v1 = mList->at(0);
        if(!v1->equals("a")) {
            printf("v1 is %s \n",v1->toChars());
            printf("LinkedList Enqueue First test5-------[FAIL] \n");
            break;
        }
        printf("LinkedList Enqueue First test6-------[OK] \n");
        break;
    }




}
