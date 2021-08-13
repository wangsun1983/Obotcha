#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ConcurrentQueue.hpp"
#include "Integer.hpp"

using namespace obotcha;

void testConcurrentQueue_ToArray() {
    while(1) {
      ConcurrentQueue<String> list = createConcurrentQueue<String>();
      list->add(createString("a"));
      list->add(createString("b"));
      list->add(createString("c"));
      ArrayList<String> ll = list->toArray();
      if(ll->size() != 3 || !ll->get(0)->equals("a")
          || !ll->get(1)->equals("b")
          || !ll->get(2)->equals("c")) {
            printf("ConcurrentQueue toArray test1-------[FAILED] \n");
            break;
          }
      break;
    }

    while(1) {
      ConcurrentQueue<int> list = createConcurrentQueue<int>();
      list->add(1);
      list->add(2);
      list->add(3);
      ArrayList<int> ll = list->toArray();
      if(ll->size() != 3 || ll->get(0) != 1
          || ll->get(1) != 2
          || ll->get(2) != 3) {
            printf("ConcurrentQueue toArray test2-------[FAILED] \n");
            break;
          }
      break;
    }

    while(1) {
      ConcurrentQueue<int> list = createConcurrentQueue<int>();
      ArrayList<int> ll = list->toArray();
      if(ll->size() != 0) {
            printf("ConcurrentQueue toArray test3-------[FAILED] \n");
            break;
          }
      break;
    }

    printf("ConcurrentQueue toArray test100-------[OK] \n");
}
