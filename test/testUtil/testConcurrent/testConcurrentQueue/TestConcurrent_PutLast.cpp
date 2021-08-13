#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ConcurrentQueue.hpp"
#include "Integer.hpp"

using namespace obotcha;

void testConcurrentQueue_PutLast() {
    while(1) {
      ConcurrentQueue<String> list = createConcurrentQueue<String>();
      list->putLast(createString("a"));
      list->putLast(createString("b"));
      list->putLast(createString("c"));
      ArrayList<String> ll = list->toArray();
      if(ll->size() != 3 || !ll->get(0)->equals("a")
          || !ll->get(1)->equals("b")
          || !ll->get(2)->equals("c")) {
            printf("ConcurrentQueue putLast test1-------[FAILED] \n");
            break;
          }
      break;
    }

    while(1) {
      ConcurrentQueue<int> list = createConcurrentQueue<int>();
      list->putLast(1);
      list->putLast(2);
      list->putLast(3);
      ArrayList<int> ll = list->toArray();
      if(ll->size() != 3 || ll->get(0) != 1
          || ll->get(1) != 2
          || ll->get(2) != 3) {
            printf("ConcurrentQueue putLast test2-------[FAILED] \n");
            break;
          }
      break;
    }

    printf("ConcurrentQueue putLast test100-------[OK] \n");
}
