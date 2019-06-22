#include <stdio.h>
#include <unistd.h>

#include "ReadWriteLock.hpp"
#include "Runnable.hpp"
#include "Thread.hpp"
#include "System.hpp"

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
  _Run2(WriteLock l) {
      mRlock = l;
  }

  void run() {
      mRlock->lock();
      sleep(10);
      mRlock->unlock();
  }

private:
  WriteLock mRlock;  
};

int main() {
    printf("---[TestReadWrite Test Start]--- \n");
    
    //ReadWriteLock()
    while(1) {
        ReadWriteLock rwLock = createReadWriteLock();
        
        if(rwLock->getReadLock() == nullptr
          ||rwLock->getWriteLock() == nullptr) {
            printf("---[TestReadWrite Test {construct()} case1] [FAILED]--- \n");
            break;
        }

        printf("---[TestReadWrite Test {construct()} case2] [Success]--- \n");
        break;
    }

    //ReadWriteLock(String)
    while(1) {
        ReadWriteLock rwLock = createReadWriteLock("test1");
        
        if(rwLock->getReadLock() == nullptr
          ||rwLock->getWriteLock() == nullptr) {
            printf("---[TestReadWrite Test {construct()} case3] [FAILED]--- \n");
            break;
        }

        ReadLock rdlock = rwLock->getReadLock();
        WriteLock wrLock = rwLock->getWriteLock();

        if(!rdlock->getName()->equals("test1") 
          ||!wrLock->getName()->equals("test1")) {
            printf("---[TestReadWrite Test {construct()} case4] [FAILED]--- \n");
            break;  
        }

        printf("---[TestReadWrite Test {construct()} case5] [Success]--- \n");
        break;
    }

    //ReadLock:Lock()
    while(1) {
      ReadWriteLock rwLock = createReadWriteLock("test1");
      Thread t1 = createThread(createRun1(rwLock->getReadLock()));
      t1->start();

      sleep(1);
      long current = st(System)::currentTimeMillis();
      rwLock->getReadLock()->lock();
      if((st(System)::currentTimeMillis() - current) != 0) {
          printf("---[TestReadLock Test {lock()} case4] [FAILED]--- \n");
          rwLock->getReadLock()->unlock();
          break;
      }
      rwLock->getReadLock()->unlock();
      
      current = st(System)::currentTimeMillis();
      rwLock->getWriteLock()->lock();
      if((st(System)::currentTimeMillis() - current) >9005) {
          printf("---[TestReadLock Test {lock()} case5] [FAILED]--- \n");
          rwLock->getWriteLock()->unlock();
          break;
      }
      rwLock->getWriteLock()->unlock();

      printf("---[TestReadLock Test {lock()} case6] [Success]--- \n");
      break;
    }

    //ReadLock::Lock(long)
    while(1) {
      ReadWriteLock rwLock = createReadWriteLock("test2");
      Thread t2 = createThread(createRun2(rwLock->getWriteLock()));
      t2->start();
      sleep(1);

      long current = st(System)::currentTimeMillis();
      int ret = rwLock->getReadLock()->lock(2000);
      long current2 = st(System)::currentTimeMillis();
      if((current2 - current) > 2005) {
        printf("---[TestReadLock Test {lock(long)} case1] [FAILED]--- \n");
        break;
      }
      
      if(ret != -ReadLockTimeout) {
        printf("---[TestReadLock Test {lock(long)} case2] [FAILED]--- \n");
        break;
      }

      printf("---[TestReadLock Test {lock(long)} case3] [Success]--- \n");
      break;

    }

    //ReadLock::tryLock()
    while(1) {
      ReadWriteLock rwLock = createReadWriteLock("test3");
      Thread t2 = createThread(createRun2(rwLock->getWriteLock()));
      t2->start();
      sleep(1);

      ReadLock rdlock = rwLock->getReadLock();
      long current = st(System)::currentTimeMillis();
      int ret = rdlock->tryLock();
      if(ret != -ReadLockLockFail) {
        printf("---[TestReadLock Test {tryLock()} case1] [FAILED]--- \n");
        break;
      }

      long v = st(System)::currentTimeMillis() - current;
      if(v > 5) {
        printf("---[TestReadLock Test {tryLock()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[TestReadLock Test {tryLock()} case3] [Success]--- \n");
      break;
    }

    //ReadLock::getName()
    while(1) {
      ReadWriteLock rwLock = createReadWriteLock("test4");
      String name = rwLock->getReadLock()->getName();
      if(!name->equals("test4")) {
        printf("---[TestReadLock Test {getName()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[TestReadLock Test {getName()} case2] [Success]--- \n");
      break;
    }

//----
    //WriteLock:Lock()
    while(1) {
      ReadWriteLock rwLock = createReadWriteLock("test1");
      Thread t1 = createThread(createRun2(rwLock->getWriteLock()));
      t1->start();
      sleep(1);
      
      long current = st(System)::currentTimeMillis();
      rwLock->getWriteLock()->lock();
      if((st(System)::currentTimeMillis() - current) > 9005) {
          printf("---[TestWriteLock Test {lock()} case1] [FAILED]--- \n");
          rwLock->getReadLock()->unlock();
          break;
      }
      rwLock->getWriteLock()->unlock();
      
      ReadWriteLock rwLock2 = createReadWriteLock("test1_1");
      Thread t2 = createThread(createRun2(rwLock2->getWriteLock()));
      t2->start();

      sleep(1);
      long current2 = st(System)::currentTimeMillis(); 
      rwLock2->getReadLock()->lock();
      if((st(System)::currentTimeMillis() - current2) > 9005) {
        printf("---[TestWriteLock Test {lock()} case2] [FAILED]--- \n");
        rwLock2->getReadLock()->unlock();
        break;
      }

      printf("---[TestWriteLock Test {lock()} case3] [Success]--- \n");
      break;
    }

    //WriteLock::Lock(long)
    while(1) {
      ReadWriteLock rwLock = createReadWriteLock("test2");
      Thread t2 = createThread(createRun1(rwLock->getReadLock()));
      t2->start();
      sleep(1);
      long current = st(System)::currentTimeMillis();
      int ret = rwLock->getWriteLock()->lock(2000);
      long current2 = st(System)::currentTimeMillis();
      if((current2 - current) > 2005) {
        printf("---[TestWriteLock Test {lock(long)} case1] [FAILED]--- \n");
        break;
      }

      if(ret != -ReadLockTimeout) {
        printf("---[TestWriteLock Test {lock(long)} case2] [FAILED]--- \n");
        break;
      }

      printf("---[TestWriteLock Test {lock(long)} case3] [Success]--- \n");
      break;

    }

    //WriteLock::tryLock()
    while(1) {
      ReadWriteLock rwLock = createReadWriteLock("test3");
      Thread t2 = createThread(createRun1(rwLock->getReadLock()));
      t2->start();

      WriteLock wrlock = rwLock->getWriteLock();
      long current = st(System)::currentTimeMillis();
      int ret = wrlock->tryLock();
      if(ret != -WriteLockLockFail) {
        printf("---[TestWriteLock Test {tryLock()} case1] [FAILED]--- \n");
        break;
      }

      long v = st(System)::currentTimeMillis() - current;
      if(v > 5) {
        printf("---[TestWriteLock Test {tryLock()} case2] [FAILED]--- \n");
        break;
      }

      printf("---[TestWriteLock Test {tryLock()} case3] [Success]--- \n");
      break;
    }

    //WriteLock::getName()
    while(1) {
      ReadWriteLock rwLock = createReadWriteLock("test4");
      String name = rwLock->getWriteLock()->getName();
      if(!name->equals("test4")) {
        printf("---[TestWriteLock Test {getName()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[TestWriteLock Test {getName()} case2] [Success]--- \n");
      break;
    }

#if 0    
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
#endif

}
