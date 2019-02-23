#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "ScheduleService.hpp"

#define TEST_DEVIATION 50 //ms
#define TEST_SLEEP_INTERVAL 1 //s

static int disposeVal = -1;

DECLARE_SIMPLE_CLASS(Run1) IMPLEMENTS(Runnable) {
public:
  void run() {
      printf("abc \n");
  }

  ~_Run1() {
    disposeVal = 10;
  }
};


int main() {
  printf("---[Thread Test Start]--- \n");
  //Test void start();
  {
      ScheduleService service = createScheduleService();
      service->execute(createRun1(),5000);
  }

  sleep(15);
  while(1){}
}
