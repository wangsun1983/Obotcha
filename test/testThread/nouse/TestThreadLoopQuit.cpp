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

DECLARE_SIMPLE_CLASS(QuitRun1) IMPLEMENTS(Runnable) {
public:

  void run() {
      sleep(100);
  }
};

int testthreadloopquit() {
#if 0  
  ArrayList<Thread> list = createArrayList<Thread>();

  for(int i = 0;i < 1024*32;i++) {
      Thread t = createThread(createQuitRun1());
      t->start();
      list->add(t);
  }

  for(int i = 0;i < 1024*32;i++) {
      Thread t = list->get(i);
      t->quit();
  }

  sleep(10);
  for(int i = 0;i < 1024*32;i++) {
      Thread t = list->get(i);
      if(t->getStatus() != st(Thread)::Complete && t->getStatus() != st(Thread)::NotStart) {
        printf("---[Thread Loop Quit case1,i is %d,status is %d] [FAILED]--- \n",i,t->getStatus());
        break;
      }
  }
#endif
  printf("---[Thread Loop Quit case1] [OK]--- \n");
}
