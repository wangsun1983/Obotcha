#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ConcurrentQueue.hpp"
#include "Integer.hpp"

using namespace obotcha;

void testConcurrentQueue_RemoveAt() {
    while(1) {
      ConcurrentQueue<String> list = createConcurrentQueue<String>();
      list->add(createString("a"));
      list->add(createString("b"));
      list->add(createString("c"));

      String v = list->removeAt(2);
      if(v != "b") {
        printf("ConcurrentQueue RemoveAt test1-------[FAILED] \n");
        break;
      }
      ArrayList<String> ll = list->toArray();
      if(ll->size() != 2 || !ll->get(0)->equals("a")
          || !ll->get(1)->equals("c")) {
            printf("ConcurrentQueue RemoveAt test1_1-------[FAILED] \n");
            break;
          }
      break;
    }

    while(1) {
      ConcurrentQueue<int> list = createConcurrentQueue<int>();
      list->add(1);
      list->add(2);
      list->add(3);
      int value = list->removeAt(1);
      ArrayList<int> ll = list->toArray();
      if(ll->size() != 2 || ll->get(0)!= 1
          || ll->get(1) != 3) {
            printf("ConcurrentQueue RemoveAt test2-------[FAILED] \n");
            break;
      }

      if(value != 2) {
        printf("ConcurrentQueue RemoveAt test2_1-------[FAILED] \n");
        break;
      }
      break;
    }

    while(1) {
      ConcurrentQueue<int> list = createConcurrentQueue<int>();
      list->add(1);
      list->add(2);
      list->add(3);
      int value = list->removeAt(0);
      ArrayList<int> ll = list->toArray();
      if(ll->size() != 2 || ll->get(0)!= 2
          || ll->get(1) != 3) {
            printf("ConcurrentQueue RemoveAt test3_1-------[FAILED] \n");
            break;
      }

      if(value != 1) {
        printf("ConcurrentQueue RemoveAt test3-------[FAILED] \n");
        break;
      }
      break;
    }

    while(1) {
      ConcurrentQueue<int> list = createConcurrentQueue<int>();
      list->add(1);
      list->add(2);
      list->add(3);

      bool isException = false;
      try {
        int index = list->removeAt(5);
      }catch(...) {
        isException = true;
      }

      if(!isException) {
        printf("ConcurrentQueue RemoveAt test4-------[FAILED] \n");
        break;
      }

      ArrayList<int> ll = list->toArray();
      if(ll->size() != 3 || ll->get(0)!= 1
          || ll->get(1) != 2
          || ll->get(2) != 3) {
            printf("ConcurrentQueue RemoveAt test4-------[FAILED] \n");
            break;
      }
      break;
    }

    while(1) {
      ConcurrentQueue<int> list = createConcurrentQueue<int>();
      list->add(1);
      list->add(2);
      list->add(3);
      int index = list->remove(3);
      ArrayList<int> ll = list->toArray();
      if(ll->size() != 2 || ll->get(0)!= 1
          || ll->get(1) != 2) {
            printf("ConcurrentQueue Remove test5-------[FAILED] \n");
            break;
      }

      if(index != 2) {
        printf("ConcurrentQueue Remove test6-------[FAILED] \n");
        break;
      }
      break;
    }

    printf("ConcurrentQueue RemoveAt test100-------[OK] \n");
}
