#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ConcurrentQueue.hpp"
#include "Integer.hpp"

using namespace obotcha;

void testConcurrentQueue_PutFirst() {
    while(1) {
      ConcurrentQueue<String> list = createConcurrentQueue<String>();
      list->putFirst(createString("a"));
      list->putFirst(createString("b"));
      list->putFirst(createString("c"));
      ArrayList<String> ll = list->toArray();
      if(ll->size() != 3 || !ll->get(0)->equals("c")
          || !ll->get(1)->equals("b")
          || !ll->get(2)->equals("a")) {
            printf("ConcurrentQueue putFirst test1-------[FAILED] \n");
            break;
          }
      break;
    }

    while(1) {
      ConcurrentQueue<int> list = createConcurrentQueue<int>();
      list->putFirst(1);
      list->putFirst(2);
      list->putFirst(3);
      ArrayList<int> ll = list->toArray();
      if(ll->size() != 3 || ll->get(0) != 3
          || ll->get(1) != 2
          || ll->get(2) != 1) {
            printf("ConcurrentQueue putFirst test2-------[FAILED] \n");
            break;
          }
      break;
    }

    while(1) {
      ConcurrentQueue<int> list = createConcurrentQueue<int>();
      ArrayList<int> ll = list->toArray();
      if(ll->size() != 0) {
            printf("ConcurrentQueue putFirst test3-------[FAILED] \n");
            break;
          }
      break;
    }

    printf("ConcurrentQueue putFirst test100-------[OK] \n");
}
