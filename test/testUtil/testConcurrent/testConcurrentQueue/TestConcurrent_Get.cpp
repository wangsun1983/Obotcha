#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ConcurrentQueue.hpp"
#include "Integer.hpp"

using namespace obotcha;

void testConcurrentQueue_Get() {
    while(1) {
      ConcurrentQueue<String> list = createConcurrentQueue<String>();
      String value = list->get(10);
      if(value != nullptr) {
        printf("ConcurrentQueue get test1-------[FAILED] \n");
        break;
      }
      break;
    }

    while(1) {
      ConcurrentQueue<int> list = createConcurrentQueue<int>();
      bool isException = false;
      try {
        list->get(10);
      } catch(...) {
        isException = true;
      }

      if(!isException) {
        printf("ConcurrentQueue get test2-------[FAILED] \n");
        break;
      }
      break;
    }

    printf("ConcurrentQueue get test100-------[OK] \n");
}
