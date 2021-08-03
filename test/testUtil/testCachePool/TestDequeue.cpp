#include <stdio.h>
#include <unistd.h>

#include "CachePool.hpp"
#include "Thread.hpp"

using namespace obotcha;

int TestDequeue() {
  while(1) {
    CachePool<String> pool = createCachePool<String>();
    String value = pool->dequeue();
    if(value != nullptr) {
      printf("CachePool TestDequeue test1 [FAIL] \n");
      break;
    }

    pool->enqueue(createString("abc"));
    value = pool->dequeue();
    if(value == nullptr || !value->equals("abc")) {
      printf("CachePool TestDequeue test2 [FAIL] \n");
      break;
    }
    break;
  }

  while(1) {
    CachePool<String> pool = createCachePool<String>(1,Global::Sync);
    pool->enqueue(createString("abc"));

    int isWaiting = 0;
    Thread t1 = createThread([&pool,&isWaiting]() {
      printf("start enqueue \n");
        pool->enqueue("aaa");
        printf("trace enqueue \n");
        isWaiting = 1;
    });
    t1->start();
    usleep(100*1000);
    if(isWaiting == 1) {
      printf("CachePool TestDequeue test3 [FAIL] \n");
      break;
    }

    String value = pool->dequeue();
    if(value == nullptr || !value->equals("abc")) {
      printf("CachePool TestDequeue test4 [FAIL] \n");
      break;
    }

    usleep(10*1000);
    if(isWaiting != 1) {
      printf("CachePool TestDequeue test5 [FAIL] \n");
      break;
    }

    value = pool->dequeue();
    if(value == nullptr || !value->equals("aaa")) {
      printf("CachePool TestDequeue test6 [FAIL] \n");
      break;
    }
    break;
  }

  printf("CachePool TestDequeue test100 [OK] \n");
  return 0;
}
