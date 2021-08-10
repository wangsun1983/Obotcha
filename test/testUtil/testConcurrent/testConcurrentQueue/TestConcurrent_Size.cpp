#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ConcurrentQueue.hpp"
#include "Integer.hpp"

using namespace obotcha;

void testConcurrentQueue_Size() {
    while(1) {
      ConcurrentQueue<int> queue = createConcurrentQueue<int>();
      if(queue->size() != 0) {
          printf("ConcurrentQueue size test1-------[FAILED] \n");
          break;
      }

      queue->putFirst(1);
      if(queue->size() != 1) {
          printf("ConcurrentQueue size test2-------[FAILED] \n");
          break;
      }

      ConcurrentQueue<int> queue2 = createConcurrentQueue<int>();
      for(int i = 0;i < 1024;i++) {
        queue2->putLast(i);
      }
      if(queue2->size() != 1024) {
        printf("ConcurrentQueue size test3-------[FAILED] \n");
        break;
      }

      break;
    }

    while(1) {
      ConcurrentQueue<String> queue = createConcurrentQueue<String>();
      if(queue->size() != 0) {
          printf("ConcurrentQueue size test4-------[FAILED] \n");
          break;
      }

      queue->putFirst(createString("a"));
      if(queue->size() != 1) {
          printf("ConcurrentQueue size test5-------[FAILED] \n");
          break;
      }

      ConcurrentQueue<String> queue2 = createConcurrentQueue<String>();
      for(int i = 0;i < 1024;i++) {
        queue2->putLast(createString(i));
      }

      if(queue2->size() != 1024) {
        printf("ConcurrentQueue size test6-------[FAILED] \n");
        break;
      }

      break;
    }
    printf("ConcurrentQueue size test100-------[OK] \n");
}
