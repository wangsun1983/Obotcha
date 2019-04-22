#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Executors.hpp"
#include "Barrier.hpp"


using namespace obotcha;

DECLARE_SIMPLE_CLASS(Run1) IMPLEMENTS(Runnable) {
public:
  _Run1(Barrier v) {
    barrier = v;
  }

  void run() {
      printf("run1 start wait \n");
      barrier->await();
      printf("run1 abc \n");
  }

  ~_Run1() {
    //disposeVal = 10;
  }
private:
  Barrier barrier;
};


DECLARE_SIMPLE_CLASS(Run2) IMPLEMENTS(Runnable) {
public:
  _Run2(Barrier v) {
    barrier = v;
  }

  void run() {
      printf("run2 start wait \n");

      barrier->await();
      printf("run2 abc \n");
  }

  ~_Run2() {
    //disposeVal = 10;
  }
private:
  Barrier barrier;
};

int main() {
  printf("---[Barrier Test Start]--- \n");
  Barrier barrier = createBarrier(2);

  Run1 r1 = createRun1(barrier);
  Thread t1 = createThread(r1);

  Run2 r2 = createRun2(barrier);
  Thread t2 = createThread(r2);

  printf("start t1 \n");
  t1->start();
  sleep(2);

  printf("start t2 \n");
  t2->start();

  sleep(15);
  while(1){}
}
