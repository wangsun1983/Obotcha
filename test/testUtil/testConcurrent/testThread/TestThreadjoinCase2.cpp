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

using namespace obotcha;

DECLARE_CLASS(JoinRunCase2) IMPLEMENTS(Runnable) {
public:
  _JoinRunCase2(int v) {
    waitInterval = v;
  }

  void run() {
    st(Thread)::msleep(waitInterval);
  }

private:
  int waitInterval;
};


int testThreadjoinCase2() {
  //sleep(1ms)
  for(int i = 0;i<1024*32;i++) {
    Thread t = createThread(createJoinRunCase2(1));
    t->start();
    t->join();
  }

  printf("---[Thread Test {JoinCase()} case1] [OK]--- \n");

  for(int i = 0;i<1024*32;i++) {
    Thread t = createThread(createJoinRunCase2(10));
    t->start();
    t->join();
  }
  printf("---[Thread Test {JoinCase()} case2] [OK]--- \n");

  for(int i = 0;i<1024;i++) {
    Thread t = createThread(createJoinRunCase2(100));
    t->start();
    t->join();
  }
  printf("---[Thread Test {JoinCase()} case3] [OK]--- \n");

  //wait(1ms)
  for(int i = 0;i<1024;i++) {
    Thread t = createThread(createJoinRunCase2(1));
    t->start();
    st(Thread)::msleep(1);
    t->join();
  }
  printf("---[Thread Test {JoinCase()} case4] [OK]--- \n");

  for(int i = 0;i<1024;i++) {
    Thread t = createThread(createJoinRunCase2(10));
    t->start();
    st(Thread)::msleep(10);
    t->join();
  }

  printf("---[Thread Test {JoinCase()} case6] [OK]--- \n");


}
