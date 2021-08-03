#include <stdio.h>
#include <unistd.h>

#include "CachePool.hpp"
#include "Thread.hpp"

using namespace obotcha;

int TestEnqueue() {
  while(1) {
    CachePool<String> pool = createCachePool<String>();
    for(int index = 0;index < 32;index++) {
      pool->enqueue(createString(index));
    }

    for(int index = 0;index < 32;index++) {
      String str = pool->dequeue();
      if(str->toBasicInt() != index) {
        printf("CachePool TestEnqueue test1 [FAIL] \n");
        break;
      }
    }
    break;
  }

  while(1) {
    CachePool<String> pool = createCachePool<String>(12,Global::Sync);
    int isWaiting = 0;
    Thread t1 = createThread([&pool,&isWaiting]() {
        pool->dequeue();
        isWaiting = 1;
    });

    t1->start();
    usleep(100);

    if(isWaiting == 1) {
      printf("CachePool TestEnqueue test2 [FAIL] \n");
      break;
    }

    pool->enqueue(createString("abc"));
    usleep(100);
    if(isWaiting != 1) {
      printf("CachePool TestEnqueue test3 [FAIL] \n");
      break;
    }

    if(pool->size() != 0) {
      printf("CachePool TestEnqueue test3 [FAIL] \n");
      break;
    }
    break;
  }

  printf("CachePool TestEnqueue test100 [OK] \n");
  return 0;
}
