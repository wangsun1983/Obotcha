#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Mutex.hpp"
#include "AutoMutex.hpp"
#include "System.hpp"

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
    while(1) {
      sleep(10);
    }
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

DECLARE_SIMPLE_CLASS(Thread4) IMPLEMENTS(Thread) {
public:
    void run() {
        //printf("thread4 run trace1 \n");
        st(Thread)::setThreadSchedPolicy(ThreadSchedPolicy::ThreadSchedFIFO);
        //printf("thread4 run trace2 \n");
        sleep(10);
    }

    ~_Thread4() {
        //printf("destroy thread4 \n");
    }
};

int policytestret = 0;

DECLARE_SIMPLE_CLASS(Thread5) IMPLEMENTS(Thread) {
public:
    void run() {
        st(Thread)::setThreadSchedPolicy(ThreadSchedPolicy::ThreadSchedFIFO);
        int v = st(Thread)::getThreadPriority();
        if(v != ThreadSchedPolicy::ThreadSchedFIFO) {
            policytestret = 1;
        }
    }
};

DECLARE_SIMPLE_CLASS(Thread6) IMPLEMENTS(Thread) {
public:
    void run() {
        st(Thread)::setThreadSchedPolicy(ThreadSchedPolicy::ThreadSchedFIFO);
        st(Thread)::setThreadPriority(ThreadPriority::ThreadHighPriority);
        sleep(10);
    }
};

int testPriorityret = 0;

DECLARE_SIMPLE_CLASS(Thread7) IMPLEMENTS(Thread) {
public:
    void run() {
        //printf("thread7 start 1 \n");
        st(Thread)::setThreadSchedPolicy(ThreadSchedPolicy::ThreadSchedFIFO);
        //printf("thread7 start 2 \n");
        st(Thread)::setThreadPriority(ThreadPriority::ThreadHighPriority);
        //printf("thread7 start v is %d \n",st(Thread)::getThreadPriority());
        if(st(Thread)::getThreadPriority() == ThreadPriority::ThreadHighPriority) {
          testPriorityret = 1;
        }
        //printf("thread7 start 4 \n");
    }
};


int testThreadCommonCase() {
  printf("---[TestThread Test Start]--- \n");

  //_Thread(String name,Runnable run);
  while(1) {
    {
        Run1 r1 = createRun1();
        Thread t = createThread("Test",r1);
        t->start();
        t->join();
    }

    if(TestData1 != 100 || disposeVal != 0) {
      printf("---[Thread Test {create()} case1] [FAILED]--- \n");
      break;
    }

    printf("---[Thread Test {create()} case2] [Success]--- \n");
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

    if(TestData1 != 100 || disposeVal != 0) {
      printf("---[Thread Test {create()} case3] [FAILED]--- \n");
      break;
  }

    printf("---[Thread Test {create()} case4] [Success]--- \n");
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

    printf("---[Thread Test {create()} case6] [Success]--- \n");
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

    printf("---[Thread Test {join(long)} case1] [Success]--- \n");
    break;
  }

  //int getStatus();
  while(1) {
    Thread2 t2 = createThread2();
    t2->setName("testgetstatus");
    t2->start();
    int status = t2->getStatus();
    if(status != ThreadRunning && status != ThreadIdle) {
      printf("---[Thread Test {getStatus()} case1,status is %d] [FAILED]--- \n",status);
      break;
    }

    t2->exit();
    sleep(1);
    status = t2->getStatus();
    if(status != ThreadComplete) {
      printf("---[Thread Test {getStatus()} case2,status is %d] [FAILED]--- \n",status);
      break;
    }

    printf("---[Thread Test {getStatus(long)} case1] [Success]--- \n");
    break;
  }


  //int setSchedPolicy(ThreadSchedPolicy);
  while(1) {
    Thread2 t2 = createThread2();
    t2->setName("testschedpolicy");
    t2->start();
    sleep(1);
    int oldSched = t2->getSchedPolicy();
    t2->setSchedPolicy(ThreadSchedFIFO);
    int sched = t2->getSchedPolicy();
    if(sched != ThreadSchedFIFO || oldSched != ThreadSchedOTHER) {
      printf("---[Thread Test {setSchedPolicy()} case1] [FAILED]--- \n");
      break;
    }

    printf("---[Thread Test {setSchedPolicy()} case2] [Sucess]--- \n");
    break;
  }

  //void setPriority(ThreadPriority priority);/getPriority()
  while(1) {
    Thread2 t2 = createThread2();
    t2->setName("setPriority_1");
    t2->start();
    sleep(1);
    int result = t2->setPriority(ThreadPriority::ThreadHighestPriority);
    int policy = t2->getSchedPolicy();
    if(policy != ThreadSchedOTHER || result != -ThreadFailNoPrioritySupport) {
      printf("---[Thread Test {setPriority()} case1] [FAILED]--- \n");
      break;
    }

    t2->setSchedPolicy(ThreadSchedPolicy::ThreadSchedFIFO);
    t2->setPriority(ThreadPriority::ThreadHighestPriority);
    if(t2->getPriority() != ThreadPriority::ThreadHighestPriority) {
      printf("---[Thread Test {setPriority()} case2] [FAILED]--- \n");
      break;
    }

    printf("---[Thread Test {setPriority()} case3] [Success]--- \n");
    break;
  }

  //setName()
  while(1) {
    Thread2 t2 = createThread2();
    t2->setName("testsetname");
    t2->start();
    t2->setName("mysetnametest");
    sleep(1);
    String name = t2->getName();
    if(name == nullptr || !name->equals("mysetnametest")) {
      printf("---[Thread Test {setName()} case1] [FAILED]--- \n");
      break;
    }

    printf("---[Thread Test {setName()} case2] [Success]--- \n");
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

    printf("---[Thread Test {getName()} case2] [Success]--- \n");
    break;
  }

  //void onInterrupt();
  while(1) {
    //printf("start onInterrupt t1 \n");
    Thread3 t1 = createThread3();
    t1->setName("onInterrupt");
    //printf("start onInterrupt t2 \n");
    t1->start();
    sleep(1);
    //printf("start onInterrupt t3 \n");
    t1->exit();
    //printf("start onInterrupt t4 \n");
    sleep(1);
    if(onInterruptCount != 1) {
        printf("---[Thread Test {onInterrupt()} case1] [FAILED]--- \n");
        break;
    }

    printf("---[Thread Test {onInterrupt()} case2] [Success]--- \n");
    break;
  }

  //void exit();
  while(1) {
      //printf("exit 1 \n");
      Thread3_1 t1 = createThread3_1();
      t1->setName("exit");
      t1->start();
      //printf("exit 2 \n");
      t1->exit();
      //printf("exit 3 \n");

      printf("---[Thread Test {exit()} case1] [Success]--- \n");
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

      st(Thread)::msleep(1000);

      long current2 = st(System)::currentTimeMillis();
      if((current2 - current) > 10005) {
          printf("---[Thread Test {msleep()} case1] [FAILED]--- \n");
          break;
      }

      printf("---[Thread Test {msleep()} case2] [Success]--- \n");
      break;
  }

  //setThreadSchedPolicy(ThreadPriority priority);
  while(1) {
    //printf("thread4 start1 \n");
    Thread4 t1 = createThread4();
    t1->setName("setThreadSchedPolicy");
    t1->start();
    //printf("thread4 start2 \n");
    sleep(10);
    if(t1->getSchedPolicy() != ThreadSchedPolicy::ThreadSchedFIFO) {
        printf("---[Thread Test {setThreadSchedPolicy()} case1] [FAILED]--- \n");
        break;
    }
    //printf("thread4 start3 \n");

    printf("---[Thread Test {setThreadSchedPolicy()} case2] [Success]--- \n");
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

    printf("---[Thread Test {getsetThreadSchedPolicyThreadPriority()} case2] [Success]--- \n");
    break;
  }

  //setThreadPriority()
  while(1) {
    Thread6 t1 = createThread6();
    t1->setName("setThreadPriority");
    t1->start();
    sleep(1);
    //t1->setPriority(ThreadPriority::ThreadHighPriority);
    printf("t1 priority is %d \n",t1->getPriority());
    if(t1->getPriority() != ThreadPriority::ThreadHighPriority) {
        printf("---[Thread Test {setThreadPriority()} case1] [FAILED]--- \n");
        break;
    }

    printf("---[Thread Test {setThreadPriority()} case1] [Success]--- \n");
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
          printf("---[Thread Test {getThreadPriority()} case1] [FAILED]--- \n");
          break;
      }

      printf("---[Thread Test {getThreadPriority()} case2] [Success]--- \n");
      break;
  }


}