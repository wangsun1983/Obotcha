#include <stdio.h>
#include <unistd.h>

#include "ReadWriteLock.hpp"
#include "Runnable.hpp"
#include "Thread.hpp"
#include "System.hpp"
#include "AtomicInteger.hpp"
#include "TimeWatcher.hpp"

using namespace obotcha;

void testReadWriteLock_Lock() {
  TimeWatcher watcher = createTimeWatcher();

  while(1) {
    ReadWriteLock rwLock = createReadWriteLock();
    rwLock->getReadLock()->lock();
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

    rwLock->getReadLock()->unlock();
    watcher->start();
    t->join();
    t1->join();
    t2->join();
    long v = watcher->stop();

    if(value->get() != 3) {
      printf("---[TestReadLock ReadWriteLock Lock case1] [FAILED]--- \n");
      break;
    }

    if(v < 300 || v > 305) {
      printf("---[TestReadLock ReadWriteLock Lock case2] [FAILED]--- \n");
      break;
    }

    break;
  }

  while(1) {
    ReadWriteLock rwLock = createReadWriteLock();
    rwLock->getWriteLock()->lock();
    AtomicInteger value = createAtomicInteger(0);
    Thread t = createThread([&value,&rwLock] {
        rwLock->getReadLock()->lock();
        usleep(100*1000);
        value->incrementAndGet();
        rwLock->getWriteLock()->unlock();
    });

    Thread t1 = createThread([&value,&rwLock] {
        rwLock->getReadLock()->lock();
        usleep(100*1000);
        value->incrementAndGet();
        rwLock->getWriteLock()->unlock();
    });

    Thread t2 = createThread([&value,&rwLock] {
        rwLock->getReadLock()->lock();
        usleep(100*1000);
        value->incrementAndGet();
        rwLock->getWriteLock()->unlock();
    });

    t->start();
    t1->start();
    t2->start();

    rwLock->getWriteLock()->unlock();
    watcher->start();
    t->join();
    t1->join();
    t2->join();
    long v = watcher->stop();

    if(value->get() != 3) {
      printf("---[TestReadLock ReadWriteLock Lock case3] [FAILED]--- \n");
      break;
    }

    if(v < 100 || v > 105) {
      printf("---[TestReadLock ReadWriteLock Lock case4] [FAILED]--- \n");
      break;
    }

    break;
  }

  while(1) {
    ReadWriteLock rwLock = createReadWriteLock();
    rwLock->getWriteLock()->lock();
    rwLock->getWriteLock()->lock();
    rwLock->getReadLock()->lock();
    printf("---[TestReadLock ReadWriteLock Lock case5] [OK]--- \n");
    break;
  }

  printf("---[TestReadLock ReadWriteLock Lock case100] [OK]--- \n");
}
