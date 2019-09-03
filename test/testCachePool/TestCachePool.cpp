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

int main() {

  printf("---[CachePool Test Start]--- \n");
  
  CachePool<Integer> t = createCachePool<Integer>(32);

  t->addCache(createInteger(1));

  Integer t2 = t->getCache();
  printf("value is %d \n",t2->toValue());
}
