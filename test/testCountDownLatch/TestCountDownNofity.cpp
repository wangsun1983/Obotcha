#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "CountDownLatch.hpp"
#include "Thread.hpp"
#include "System.hpp"
#include "AtomicInteger.hpp"

using namespace obotcha;

CountDownLatch notifylatch = createCountDownLatch(1);
AtomicInteger latchvalue = createAtomicInteger(0);

DECLARE_SIMPLE_CLASS(CountDownRunnable) IMPLEMENTS(Runnable) {
public:
  void run() {
      notifylatch->await();
      latchvalue->incrementAndGet();
  }
};

int notifytest() {
    //test1
    for(int i = 0;i<512;i++) {
      Thread t = createThread(createCountDownRunnable());
      t->start();
    }

    notifylatch->countDown();
    sleep(1);
    if(latchvalue->get() != 512) {
        printf("---[TestScheduledThreadPoolExecutor Test {notify()} case1] [FAILED]--- \n");
    }

    printf("---[TestScheduledThreadPoolExecutor Test {notify()} case100] [OK]--- \n");
}
