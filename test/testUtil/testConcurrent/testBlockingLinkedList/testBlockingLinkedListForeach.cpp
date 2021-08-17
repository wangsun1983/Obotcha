#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingLinkedList.hpp"
#include "Integer.hpp"
#include "System.hpp"

using namespace obotcha;

void testBlockingLinkedListForeach() {

    while(1) {
        BlockingLinkedList<int> list = createBlockingLinkedList<int>(5);
        list->putFirst(1);
        list->putFirst(2);
        list->putFirst(3);
        list->putFirst(4);
        list->putFirst(5);
        int sum = 0;
        list->foreach([&sum](int v) {
            sum += v;
            return Global::Continue;
        });

        if(sum != 15) {
          printf("BlockingLinkedList<int> Foreach test1-------[FAILED] \n");
        }

        break;
    }

    printf("BlockingLinkedList<int> Foreach test100-------[OK] \n");

}
