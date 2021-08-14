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

int testThreadLoopStart() {
  while(1) {
    Thread t = createThread([] {

    });
    if(t->start() != 0) {
      printf("---[Thread Loop start case1] [FAILED]--- \n");
      break;
    }

    if(t->start() != -AlreadyExecute) {
      printf("---[Thread Loop start case2] [FAILED]--- \n");
      break;
    }
    break;
  }
  printf("---[Thread Loop start case100] [OK]--- \n");
  return 0;
}
