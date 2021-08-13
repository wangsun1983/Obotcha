#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ConcurrentQueue.hpp"
#include "Integer.hpp"

using namespace obotcha;

void testConcurrentQueue_MultiThread_Case2() {
    while(1) {
      ConcurrentQueue<String> list = createConcurrentQueue<String>();
      ArrayList<Thread> threads = createArrayList<Thread>();

      //get result
      long result = 0;
      for(int i = 1;i<1024*32;i++) {
        result += i;
      }

      for(int j = 0;j<16;j++) {
        Thread t = createThread([&list] {
          for(int i = 1;i<1024*32;i++) {
            list->putLast(createString(i));
          }
          list->putLast(createString(-1));
        });
        t->start();
        threads->add(t);
      }

      long sum = 0;
      int finishCount = 0;
      while(finishCount != 16) {
        String str = list->takeFirst();
        int v = str->toBasicInt();
        if(v == -1) {
          finishCount++;
          continue;
        }
        sum += v;
      }

      if(sum != 16*result) {
        printf("ConcurrentQueue MultiThread Case2 test1-------[FAILED],sum is %ld \n",sum);
      }
      break;
    }

    printf("ConcurrentQueue MultiThread Case2 test100-------[OK] \n");
}
