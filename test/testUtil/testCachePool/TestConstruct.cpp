#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "Long.hpp"
#include "Log.hpp"
#include "FifoPipe.hpp"
#include "CachePool.hpp"

using namespace obotcha;

int TestConstruct() {
  while(1) {
    CachePool<String> pool = createCachePool<String>(32);
    if(pool->capacity() != 32) {
      printf("CachePool TestConstruct test1 [FAIL] \n");
      break;
    }

    String data = pool->dequeue();
    if(data != nullptr) {
      printf("CachePool TestConstruct test2 [FAIL] \n");
      break;
    }
    break;
  }

  while(1) {
    CachePool<String> pool = createCachePool<String>(16);
    if(pool->capacity() != 16) {
      printf("CachePool TestConstruct test3 [FAIL] \n");
      break;
    }

    String data = pool->dequeue();
    if(data != nullptr) {
      printf("CachePool TestConstruct test4 [FAIL] \n");
      break;
    }
    break;
  }

  printf("CachePool TestConstruct test100 [OK] \n");
  return 0;
}
