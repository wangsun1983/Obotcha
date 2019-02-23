#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"

#define TEST_DEVIATION 50 //ms
#define TEST_SLEEP_INTERVAL 1 //s

static int disposeVal = -1;

DECLARE_SIMPLE_CLASS(Run1) IMPLEMENTS(Runnable) {
public:
  void run() {
      sleep(TEST_SLEEP_INTERVAL);
  }

  ~_Run1() {
    disposeVal = 10;
  }
};

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
