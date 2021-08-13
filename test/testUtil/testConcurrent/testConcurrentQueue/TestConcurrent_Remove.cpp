#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ConcurrentQueue.hpp"
#include "Integer.hpp"

using namespace obotcha;

void testConcurrentQueue_Remove() {
    while(1) {
      ConcurrentQueue<String> list = createConcurrentQueue<String>();
      list->add(createString("a"));
      list->add(createString("b"));
      list->add(createString("c"));

      int index = list->remove(createString("b"));
      if(index != 1) {
        printf("ConcurrentQueue Remove test1-------[FAILED] \n");
        break;
      }
      ArrayList<String> ll = list->toArray();
      if(ll->size() != 2 || !ll->get(0)->equals("a")
          || !ll->get(1)->equals("c")) {
            printf("ConcurrentQueue Remove test1_1-------[FAILED] \n");
            break;
          }
      break;
    }

    while(1) {
      ConcurrentQueue<int> list = createConcurrentQueue<int>();
      list->add(1);
      list->add(2);
      list->add(3);
      int index = list->remove(2);
      ArrayList<int> ll = list->toArray();
      if(ll->size() != 2 || ll->get(0)!= 1
          || ll->get(1) != 3) {
            printf("ConcurrentQueue Remove test2-------[FAILED] \n");
            break;
      }

      if(index != 1) {
        printf("ConcurrentQueue Remove test2_1-------[FAILED] \n");
        break;
      }
      break;
    }

    while(1) {
      ConcurrentQueue<int> list = createConcurrentQueue<int>();
      list->add(1);
      list->add(2);
      list->add(3);
      int index = list->remove(1);
      ArrayList<int> ll = list->toArray();
      if(ll->size() != 2 || ll->get(0)!= 2
          || ll->get(1) != 3) {
            printf("ConcurrentQueue Remove test3_1-------[FAILED] \n");
            break;
      }

      if(index != 0) {
        printf("ConcurrentQueue Remove test3-------[FAILED] \n");
        break;
      }
      break;
    }

    while(1) {
      ConcurrentQueue<int> list = createConcurrentQueue<int>();
      list->add(1);
      list->add(2);
      list->add(3);
      int index = list->remove(5);
      ArrayList<int> ll = list->toArray();
      if(ll->size() != 3 || ll->get(0)!= 1
          || ll->get(1) != 2
          || ll->get(2) != 3) {
            printf("ConcurrentQueue Remove test4-------[FAILED] \n");
            break;
      }

      if(index != -1) {
        printf("ConcurrentQueue Remove test4-------[FAILED] \n");
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

    printf("ConcurrentQueue Remove test100-------[OK] \n");
}
