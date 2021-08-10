#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ConcurrentQueue.hpp"
#include "Integer.hpp"

using namespace obotcha;

void testConcurrentQueue_Add() {
    while(1) {
      ConcurrentQueue<String> list = createConcurrentQueue<String>();
      for(int i = 0;i<1024;i++) {
        list->add(createString(i));
      }

      for(int j = 0;j<1024;j++) {
        String v = list->get(j);
        if(v->toBasicInt() != j) {
          printf("ConcurrentQueue add test1-------[FAILED],v is %d,j is %d \n",v->toBasicInt(),j);
        }
      }
      break;
    }

    while(1) {
      ConcurrentQueue<int> list = createConcurrentQueue<int>();
      for(int i = 0;i<1024;i++) {
        list->add(i);
      }

      for(int j = 0;j<1024;j++) {
        int v = list->get(j);
        if(v != j) {
          printf("ConcurrentQueue add test2-------[FAILED],v is %d,j is %d \n",v,j);
        }
      }
      break;
    }

    printf("ConcurrentQueue add test100-------[OK] \n");
}
