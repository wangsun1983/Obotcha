#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Mutex.hpp"
#include "AutoLock.hpp"
#include "System.hpp"
#include "Error.hpp"

#define TEST_DEVIATION 50 //ms
#define TEST_SLEEP_INTERVAL 100 //s

static int disposeVal = -1;

using namespace obotcha;

int TestData1 = 1;

int TestData2 = 2;
int disposeData2 = -1;

DECLARE_SIMPLE_CLASS(Run1) IMPLEMENTS(Runnable) {
public:

  void run() {
      TestData1 = 100;
  }

  ~_Run1() {
    disposeVal = 0;
  }
};

DECLARE_SIMPLE_CLASS(Thread1) IMPLEMENTS(Thread) {
public:

  void run() {
      TestData2 = 100;
  }

  ~_Thread1() {
    disposeData2 = 0;
  }
};

DECLARE_SIMPLE_CLASS(Thread2) IMPLEMENTS(Thread) {
public:
  //_Thread(String name,Runnable run);
  void run() {
    //while(1) {
      sleep(10*1000);
    //}
  }
};

int onInterruptCount = 0;

DECLARE_SIMPLE_CLASS(Thread3) IMPLEMENTS(Thread) {
public:
    void run() {
        while(1) {
            sleep(1);
        }
    }

    void onInterrupt() {
        onInterruptCount = 1;
    }
};

DECLARE_SIMPLE_CLASS(Thread3_1) IMPLEMENTS(Thread) {
public:
    void run() {
        while(1) {
            sleep(1);
        }
    }

    void onInterrupt() {
        onInterruptCount = 1;
    }
};

#if 0
DECLARE_SIMPLE_CLASS(Thread4) IMPLEMENTS(Thread) {
public:
    void run() {
        int ret = st(Thread)::setThreadSchedPolicy(st(Thread)::SchedFifo);
        sleep(10*1000);
    }

    ~_Thread4() {
        //printf("destroy thread4 \n");
    }
};

int policytestret = 0;

DECLARE_SIMPLE_CLASS(Thread5) IMPLEMENTS(Thread) {
public:
    void run() {
        int ret = st(Thread)::setThreadSchedPolicy(st(Thread)::SchedFifo);
        int v = st(Thread)::getSchedPolicy();
        if(v == st(Thread)::SchedFifo) {
            policytestret = 1;
        }
    }
};


DECLARE_SIMPLE_CLASS(Thread6) IMPLEMENTS(Thread) {
public:
    void run() {
        st(Thread)::setThreadSchedPolicy(st(Thread)::SchedFifo);
        st(Thread)::setThreadPriority(st(Thread)::HighPriority);
        sleep(10);
    }
};

int testPriorityret = 0;

DECLARE_SIMPLE_CLASS(Thread7) IMPLEMENTS(Thread) {
public:
    void run() {
        //printf("thread7 start 1 \n");
        st(Thread)::setThreadSchedPolicy(st(Thread)::SchedFifo);
        //printf("thread7 start 2 \n");
        st(Thread)::setThreadPriority(st(Thread)::HighPriority);
        if(st(Thread)::getThreadPriority() == st(Thread)::HighPriority) {
          testPriorityret = 1;
        }
        //printf("thread7 start 4 \n");
    }
};
#endif

int testThreadCommonCase() {
  printf("---[TestThread Test Start]--- \n");


  //_Thread(String name,Runnable run);
  while(1) {
    {
        Run1 r1 = createRun1();
        Thread t = createThread(r1);
        t->start();
        t->join();
    }
    st(Thread)::sleep(1000);

    if(TestData1 != 100 || disposeVal != 0) {
      printf("---[Thread Test {create()} case1] [FAILED],TestData1 is %d,disposeVal is %d--- \n",TestData1,disposeVal);
      break;
    }

    printf("---[Thread Test {create()} case2] [OK]--- \n");
    break;
  }



  //_Thread(Runnable run);
  while(1){
    disposeVal = -1;
    {
        Run1 r1 = createRun1();
        Thread t = createThread(r1);
        t->setName("testrunnable");
        t->start();
        t->join();
    }
    st(Thread)::sleep(1000);
    
    if(TestData1 != 100 || disposeVal != 0) {
      printf("---[Thread Test {create()} case3] [FAILED]--- \n");
      break;
  }

    printf("---[Thread Test {create()} case4] [OK]--- \n");
    break;
}


  //_Thread()
  while(1) {
    {
      Thread1 t1 = createThread1();
      t1->setName("_thread");
      t1->start();
      t1->join();
    }
    sleep(1); //wait thread remove
    if(TestData2 != 100 || disposeData2 != 0) {
      printf("---[Thread Test {create()} case5] [FAILED]--- \n");
      break;
    }

    printf("---[Thread Test {create()} case6] [OK]--- \n");
    break;
  }


  //void join(long millseconds);
  while(1) {
    Thread2 t2 = createThread2();
    t2->setName("testjoinThread");
    t2->start();
    long int start = st(System)::currentTimeMillis();
    t2->join(5000);
    long int end = st(System)::currentTimeMillis();
    int v = (end - start);
    if((end - start - 5000) > 10) {
      printf("---[Thread Test {join(long)} case1] [FAILED]--- \n");
      break;
    }

    printf("---[Thread Test {join(long)} case1] [OK]--- \n");
    break;
  }


  //int getStatus();
  while(1) {
    Thread2 t2 = createThread2();
    t2->setName("testgetstatus");
    t2->start();
    int status = t2->getStatus();
    if(status != st(Thread)::Running && status != st(Thread)::Idle) {
      printf("---[Thread Test {getStatus()} case1,status is %d] [FAILED]--- \n",status);
      break;
    }

    sleep(1);
    status = t2->getStatus();
    if(status != st(Thread)::Running) {
      printf("---[Thread Test {getStatus()} case2,status is %d] [FAILED]--- \n",status);
      break;
    }

    printf("---[Thread Test {getStatus(long)} case1] [OK]--- \n");
    break;
  }

#if 0
  //int setSchedPolicy(ThreadSchedPolicy);
  while(1) {
    Thread2 t2 = createThread2();
    t2->setName("testschedpolicy");
    t2->start();
    sleep(1);
    int oldSched = t2->getSchedPolicy();
    t2->setSchedPolicy(st(Thread)::SchedFifo);
    int sched = t2->getSchedPolicy();
    if(sched != st(Thread)::SchedFifo || oldSched != st(Thread)::SchedOther) {
      printf("---[Thread Test {setSchedPolicy()} case1] [FAILED]--- \n");
      break;
    }
    printf("---[Thread Test {setSchedPolicy()} case2] [OK]--- \n");
    break;
  }


  //void setPriority(ThreadPriority priority);/getPriority()

  while(1) {
    Thread2 t2 = createThread2();
    t2->setName("setPriority_1");
    t2->start();
    sleep(1);
    int result = t2->setPriority(st(Thread)::HighestPriority);
    int policy = t2->getSchedPolicy();
    if(policy != st(Thread)::SchedOther || result == -1) {
      printf("---[Thread Test {setPriority()} case1] [FAILED]--- \n");
      break;
    }

    printf("start priority test \n");
    int result1 = t2->setSchedPolicy(st(Thread)::SchedFifo);
    int result2 = t2->setPriority(st(Thread)::HighestPriority);
    printf("result1 is %d,result2 is %d \n",result1,result2);
    if(t2->getPriority() != st(Thread)::HighestPriority) {
      printf("---[Thread Test {setPriority()} case2] [FAILED],t2->getPriority() is %d--- \n",t2->getPriority());
      break;
    }
    
    printf("---[Thread Test {setPriority()} case3] [OK]--- \n");
    break;
  }
#endif
  
  //setName()
  while(1) {
    Thread2 t2 = createThread2();
    t2->setName("testsetname");
    t2->start();
    //printf("t2_1 status is %d \n",t2->getStatus());
    t2->setName("mysetnametest");
    //printf("t2_2 status is %d \n",t2->getStatus());
    sleep(1);
    String name = t2->getName();
    //if(name == nullptr) {
    //  printf("name is nullptr \n");
    //} else {
    //  printf("name is %s \n",name->toChars());
    //}

    if(name == nullptr || !name->equals("mysetnametest")) {
      printf("---[Thread Test {setName()} case1] [FAILED]--- \n");
      break;
    }

    
    printf("---[Thread Test {setName()} case2] [OK]--- \n");
    break;
  }

  //getName()
  while(1) {
    Thread2 t2 = createThread2();
    t2->start();
    t2->setName("mygetnametest");

    String name = t2->getName();
    if(name == nullptr || !name->equals("mygetnametest")) {
      printf("---[Thread Test {getName()} case1] [FAILED]--- \n");
      break;
    }

    
    printf("---[Thread Test {getName()} case2] [OK]--- \n");
    break;
  }

  //static void yield();
  while(1) {
      //not test
      printf("---[Thread Test {yield()} case1] [Not Test]--- \n");
      break;
  }

  //void msleep(unsigned long);
  while(1) {
      long current = st(System)::currentTimeMillis();

      st(Thread)::sleep(1000);

      long current2 = st(System)::currentTimeMillis();
      if((current2 - current) > 1005) {
          printf("---[Thread Test {msleep()} case1] [FAILED]--- \n");
          break;
      }

      printf("---[Thread Test {msleep()} case2] [OK]--- \n");
      break;
  }

#if 0 
  //setThreadSchedPolicy(ThreadPriority priority);
  while(1) {
    Thread4 t1 = createThread4();
    t1->start();
    sleep(1);
    int policy = t1->getSchedPolicy();
    if(policy != st(Thread)::SchedFifo) {
        printf("---[Thread Test {setThreadSchedPolicy()} case1] [FAILED],policy is %d--- \n",policy);
        break;
    }

    
    printf("---[Thread Test {setThreadSchedPolicy()} case2] [OK]--- \n");
    break;
  }

  //getThreadPriority()
 
  while(1) {
    Thread5 t1 = createThread5();
    t1->setName("getThreadPriority");
    t1->start();
    t1->join();
    sleep(1);
    if(policytestret != 1) {
        printf("---[Thread Test {getThreadPriority()} case1] [FAILED]--- \n");
        break;
    }
    
    printf("---[Thread Test {getsetThreadSchedPolicyThreadPriority()} case2] [OK]--- \n");
    break;
  }


  //setThreadPriority()
  while(1) {
    Thread6 t1 = createThread6();
    t1->setName("setThreadPriority");
    t1->start();
    sleep(1);
    //t1->setPriority(ThreadPriority::ThreadHighPriority);
    //printf("t1 priority is %d \n",t1->getPriority());
    if(t1->getPriority() != st(Thread)::HighPriority) {
        printf("---[Thread Test {setThreadPriority()} case1] [FAILED]--- \n");
        break;
    }
    
    printf("---[Thread Test {setThreadPriority()} case1] [OK]--- \n");
    break;
  }

  //int getThreadPriority();
  while(1) {
      Thread7 t1 = createThread7();
      t1->setName("getThreadPriority");
      //printf("abc1 \n");
      t1->start();
      //printf("abc2 \n");
      t1->join();
      //printf("abc3 \n");

      if(testPriorityret != 1) {
          printf("---[Thread Test {getThreadPriority()} case1__] [FAILED]--- \n");
          break;
      }
      

      printf("---[Thread Test {getThreadPriority()} case2] [OK]--- \n");
      break;
  }
#endif

}
