#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Executors.hpp"
#include "Barrier.hpp"
#include "AtomicInteger.hpp"


using namespace obotcha;

AtomicInteger loopValue = createAtomicInteger(0);
Barrier barrier_257 = createBarrier(256 + 1);

DECLARE_SIMPLE_CLASS(LoopSubmitRun) IMPLEMENTS(Runnable) {
public:
    void run() {
      barrier_257->await();
      loopValue->incrementAndGet();
    }
};

int looptest() {
  //test1
  for(int i = 0;i < 256;i++) {
    Thread t = createThread(createLoopSubmitRun());
    t->start();
  }
  barrier_257->await();
  sleep(1);
  if(loopValue->get() != 256) {
    printf("---[Barrier Test {loop test} case1] [FAIL]--- \n");
    return 0;
  }

  printf("---[Barrier Test {loop test} case100] [OK]--- \n");
  return 0;
}
