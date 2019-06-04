#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Mutex.hpp"
#include "AutoMutex.hpp"

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

int main() {
  printf("---[Thread Test Start]--- \n");
  //_Thread(String name,Runnable run);
  while(1) {
    {
        printf("abc1 \n");
        Run1 r1 = createRun1();
        Thread t = createThread("Test",r1);
        printf("abc1 \n");
        t->start();
        printf("abc2 \n");
        t->join();
        printf("abc3 \n");
    }

    if(TestData1 != 100 || disposeVal != 0) {
      printf("---[Thread Test {create()} case1] [FAILED]--- \n");
      break;
    }

    printf("---[Thread Test {create()} case2] [Success]--- \n");
    break;
  }


#if 0
  //_Thread(Runnable run);
  while(1){
    disposeVal = -1;
    {
        Run1 r1 = createRun1();
        Thread t = createThread(r1);
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
      t1->start();
      t1->join();
    }

    if(TestData2 != 100 || disposeData2 != 0) {
      printf("TestData2 is %d,disposeData2 is %d \n",TestData2,disposeData2);
      printf("---[Thread Test {create()} case5] [FAILED]--- \n");
      break;
    }

    printf("---[Thread Test {create()} case6] [Success]--- \n");
    break;
  }

  //printf("---[Thread Test {create()} case6] [End]--- \n");
#endif
}


#if 0
DECLARE_SIMPLE_CLASS(Run2) IMPLEMENTS(Runnable) {
public:
  void run() {
    printf("run2 start \n");
    sleep(1000*10);
    printf("run2 start2 \n");
  }

  ~_Run2() {
    printf("Runn2 dispose \n");
  }

  void onInterrupt() {
    printf("Run2 onInterrupt \n");
  }
};

DECLARE_SIMPLE_CLASS(Run3) IMPLEMENTS(Runnable) {
public:
  _Run3(Thread t) {
      thread = t;
  }

  void run() {
    sleep(3);
    printf("start exit \n");
    thread->exit();
    printf("exit!!! \n");
  }

  void onInterrupt() {
    printf("Run3 onInterrupt \n");
  }

private:
  Thread thread;
};

int main() {
  printf("---[Thread Test Start]--- \n");
  //Test void start();
  {
      Thread t = createThread(createRun1());
      long int start = st(System)::currentTimeMillis();

      t->start();
      t->join();

      long int end = st(System)::currentTimeMillis();

      int result = end - start;
      if((result < TEST_SLEEP_INTERVAL*1000 + 50)
        && (result >= TEST_SLEEP_INTERVAL*1000)) {
        printf("Thread start test-------[OK] \n");
        printf("Thread join test-------[OK] \n");
      } else {
        printf("Thread start test-------[FAIL] \n");
        printf("Thread join test-------[FAIL] \n");
      }
  }

  sleep(5);

  //Test runnable release
  if(disposeVal == 10) {
    printf("Thread runnable release test-------[OK] \n");
  } else {
    printf("Thread runnable release test-------[FAIL] \n");
  }

  //Test Cancel
  {
    Thread t = createThread(createRun2());
    t->start();
    Thread t2 = createThread(createRun3(t));
    t2->start();
    t->join();

    printf("Thread runnable cancel test-------[OK] \n");
  }

  //while(1){}
}
#endif
