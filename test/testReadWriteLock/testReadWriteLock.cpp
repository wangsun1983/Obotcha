#include <stdio.h>
#include <unistd.h>

#include "ReadWriteLock.hpp"
#include "Runnable.hpp"
#include "Thread.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(Run1) IMPLEMENTS(Runnable) {
public:
  _Run1(ReadLock l) {
      mRlock = l;
  }

  void run() {
      mRlock->lock();
      sleep(10);
      mRlock->unlock();
  }

private:
  ReadLock mRlock;  
};

DECLARE_SIMPLE_CLASS(Run2) IMPLEMENTS(Runnable) {
public:
  _Run2(ReadLock l) {
      mRlock = l;
  }

  void run() {
      mRlock->lock();
      int index = 0;
      while(index < 9) {
        printf("index is %d \n",index);
        sleep(1);
        index++;
      }
      mRlock->unlock();
  }

private:
  ReadLock mRlock;  
};

DECLARE_SIMPLE_CLASS(Run3) IMPLEMENTS(Runnable) {
public:
  _Run3(WriteLock l) {
      mWlock = l;
  }

  void run() {
      sleep(1);
      printf("i start write!!!!! \n");
      mWlock->lock();
      while(1) {
          printf("i write trace!!!!! \n");
          sleep(1);
      }
      mWlock->unlock();
  }

private:
  WriteLock mWlock;  
};

int main() {
    ReadWriteLock rwLock = createReadWriteLock();
    Thread t1 = createThread(createRun1(rwLock->getReadLock()));
    Thread t2 = createThread(createRun2(rwLock->getReadLock()));
    Thread t3 = createThread(createRun3(rwLock->getWriteLock()));

    t1->start();
    t2->start();
    t3->start();

    while(1) {
        sleep(11);
    }

}
