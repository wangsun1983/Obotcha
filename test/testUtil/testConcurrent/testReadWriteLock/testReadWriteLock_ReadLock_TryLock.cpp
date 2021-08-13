#include <stdio.h>
#include <unistd.h>

#include "ReadWriteLock.hpp"
#include "Runnable.hpp"
#include "Thread.hpp"
#include "System.hpp"
#include "AtomicInteger.hpp"
#include "TimeWatcher.hpp"

using namespace obotcha;

void testReadLock_TryLock() {
  TimeWatcher watcher = createTimeWatcher();

  while(1) {
    ReadWriteLock rwLock = createReadWriteLock();
    rwLock->getWriteLock()->lock();
    AtomicInteger value = createAtomicInteger();
    Thread t = createThread([&rwLock]{
      rwLock->getReadLock()->tryLock();
    });
    break;
  }

  printf("---[TestReadLock ReadLock Lock case100] [OK]--- \n");
}
