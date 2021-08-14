#include <stdio.h>
#include <unistd.h>

#include "ReadWriteLock.hpp"
#include "Runnable.hpp"
#include "Thread.hpp"
#include "System.hpp"
#include "AtomicInteger.hpp"
#include "TimeWatcher.hpp"

using namespace obotcha;

void testWriteLock_TryLock() {
  TimeWatcher watcher = createTimeWatcher();

  while(1) {
    ReadWriteLock rwLock = createReadWriteLock();
    rwLock->getWriteLock()->lock();
    AtomicInteger value = createAtomicInteger();
    Thread t = createThread([&rwLock,&value]{
      int ret = rwLock->getWriteLock()->tryLock();
      if(ret != -LockBusy) {
        printf("---[TestReadLock WriteLock TryLock case1] [FAIL]--- \n");
      }
      value->incrementAndGet();
    });
    t->start();
    usleep(1000);

    if(value->get() != 1) {
      printf("---[TestReadLock WriteLock TryLock case2] [FAIL]--- \n");
    }
    break;
  }

  while(1) {
    ReadWriteLock rwLock = createReadWriteLock();
    rwLock->getReadLock()->lock();
    AtomicInteger value = createAtomicInteger();
    Thread t = createThread([&rwLock,&value]{
      int ret = rwLock->getWriteLock()->tryLock();
      if(ret != -LockBusy) {
        printf("---[TestReadLock WriteLock TryLock case3] [FAIL]--- \n");
      }
      value->incrementAndGet();
    });
    t->start();
    usleep(1000);

    if(value->get() != 1) {
      printf("---[TestReadLock WriteLock TryLock case4] [FAIL]--- \n");
    }
    break;
  }

  printf("---[TestReadLock WriteLock TryLock case100] [OK]--- \n");
}
