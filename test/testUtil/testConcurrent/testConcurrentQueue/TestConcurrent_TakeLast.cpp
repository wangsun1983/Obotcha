#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ConcurrentQueue.hpp"
#include "Integer.hpp"

using namespace obotcha;

void testConcurrentQueue_TakeLast() {
    while(1) {
      ConcurrentQueue<String> list = createConcurrentQueue<String>();
      list->add(createString("a"));
      list->add(createString("b"));
      list->add(createString("c"));
      ArrayList<String> ll = list->toArray();
      for(int i = 0;i < 3;i++) {
        auto v = list->takeLast();
        if(v != ll->get(2-i)) {
          printf("ConcurrentQueue taktLast test1-------[FAILED] \n");
          break;
        }
      }
      break;
    }

    while(1) {
      ConcurrentQueue<int> list = createConcurrentQueue<int>();
      list->add(1);
      list->add(2);
      list->add(3);
      ArrayList<int> ll = list->toArray();
      for(int i = 0;i < 3;i++) {
        auto v = list->takeLast();
        if(v != ll->get(2-i)) {
          printf("ConcurrentQueue taktLast test100-------[FAILED] \n");
          break;
        }
      }
      break;
    }

    while(1) {
      ConcurrentQueue<int> list = createConcurrentQueue<int>();
      bool isException = false;
      try {
        list->takeLast();
      } catch(...) {
        isException = true;
      }

      if(!isException) {
        printf("ConcurrentQueue taktLast test100-------[FAILED] \n");
        break;
      }
      break;
    }

    printf("ConcurrentQueue taktLast test100-------[OK] \n");
}
