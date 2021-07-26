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
#include "InterruptedException.hpp"


using namespace obotcha;



DECLARE_SIMPLE_CLASS(JoinRun1) IMPLEMENTS(Runnable) {
public:

  void run() {
      
  }

};


int testThreadQuickJoin() {
  printf("---[TestThread Sleep Start]--- \n");

  while(1) {
    for(int i = 0;i < 1024*32;i++) {
      Thread t = createThread(createJoinRun1());
      t->start();
      t->join();
    }
    printf("---[Thread Test {Quick Join()} case1] [Success] \n");
    break;
  }
  
  return 0;
  
}
