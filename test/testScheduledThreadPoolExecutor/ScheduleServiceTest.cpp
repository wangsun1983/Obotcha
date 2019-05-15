#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Executors.hpp"
#include "ScheduledExecutorService.hpp"
#include "ScheduledThreadPoolExecutor.hpp"

#define TEST_DEVIATION 50 //ms
#define TEST_SLEEP_INTERVAL 1 //s

static int disposeVal = -1;

using namespace obotcha;

DECLARE_SIMPLE_CLASS(Run1) IMPLEMENTS(Runnable) {
public:
  void run() {
      printf("abc \n");
  }

  ~_Run1() {
    disposeVal = 10;
  }
};

void testDestroyFunc() {
  ScheduledThreadPoolExecutor service = createScheduledThreadPoolExecutor();
  service->schedule(createRun1(),5000l);
  service->schedule(createRun1(),5000l);
  service->schedule(createRun1(),5000l);
}

int main() {
  printf("---[Thread Test Start]--- \n");
  //Test void start();
#if 0
  {
      ScheduledThreadPoolExecutor service = createScheduledThreadPoolExecutor();
      service->schedule(createRun1(),5000l);
  }
#endif
  testDestroyFunc();

  sleep(15);
  while(1){}
}
