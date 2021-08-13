#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ConcurrentQueue.hpp"
#include "Integer.hpp"

using namespace obotcha;

void testConcurrentQueue_Clear() {
    while(1) {
      ConcurrentQueue<String> list = createConcurrentQueue<String>();
      list->add(createString("a"));
      list->add(createString("b"));
      list->add(createString("c"));
      if(list->size() != 3) {
        printf("ConcurrentQueue clear test1-------[FAILED] \n");
        break;
      }

      list->clear();
      if(list->size() != 0) {
        printf("ConcurrentQueue clear test2-------[FAILED] \n");
        break;
      }
      break;
    }
    printf("ConcurrentQueue clear test100-------[OK] \n");
}
