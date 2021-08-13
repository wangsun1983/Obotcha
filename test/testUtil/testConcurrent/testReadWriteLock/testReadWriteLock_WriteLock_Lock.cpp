#include <stdio.h>
#include <unistd.h>

#include "ReadWriteLock.hpp"
#include "Runnable.hpp"
#include "Thread.hpp"
#include "System.hpp"
#include "AtomicInteger.hpp"
#include "TimeWatcher.hpp"

using namespace obotcha;

void testWriteLock_Lock() {
  TimeWatcher watcher = createTimeWatcher();

  while(1) {
    ReadWriteLock rwLock = createReadWriteLock();
    rwLock->getWriteLock()->lock();
    AtomicInteger value = createAtomicInteger(0);
    Thread t = createThread([&value,&rwLock] {
        rwLock->getWriteLock()->lock();
        usleep(100*1000);
        value->incrementAndGet();
        rwLock->getWriteLock()->unlock();
    });

    Thread t1 = createThread([&value,&rwLock] {
        rwLock->getWriteLock()->lock();
        usleep(100*1000);
        value->incrementAndGet();
        rwLock->getWriteLock()->unlock();
    });

    Thread t2 = createThread([&value,&rwLock] {
        rwLock->getWriteLock()->lock();
        usleep(100*1000);
        value->incrementAndGet();
        rwLock->getWriteLock()->unlock();
    });

    t->start();
    t1->start();
    t2->start();

    usleep(10*1000);
    watcher->start();
    rwLock->getWriteLock()->unlock();

    t->join();
    t1->join();
    t2->join();

    long v = watcher->stop();
    if(v < 300 || v > 305) {
      printf("---[TestReadLock WriteLock Lock case1] [FAILED]--- \n");
      break;
    }

    if(value->get() != 3) {
      printf("---[TestReadLock WriteLock Lock case2] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    ReadWriteLock rwLock = createReadWriteLock();
    rwLock->getWriteLock()->lock();
    rwLock->getWriteLock()->lock();
    printf("---[TestReadLock WriteLock Lock case3] [OK]--- \n");
    break;
  }

  while(1) {
    ReadWriteLock rwLock = createReadWriteLock();
    Thread t = createThread([&rwLock]() {
      rwLock->getWriteLock()->lock();
      usleep(200*1000);
      rwLock->getWriteLock()->unlock();
    });
    t->start();
    usleep(100*1000);

    watcher->start();
    rwLock->getWriteLock()->lock(100);
    long v = watcher->stop();
    if(v < 100 || v > 105) {
      printf("---[TestReadLock WriteLock Lock case4] [FAILED]--- \n");
      break;
    }
    t->join();
    break;
  }

  printf("---[TestReadLock ReadLock Lock case100] [OK]--- \n");
}
