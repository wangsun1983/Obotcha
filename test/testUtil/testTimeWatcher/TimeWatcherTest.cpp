#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "Long.hpp"
#include "TimeWatcher.hpp"

using namespace obotcha;

int main() {

  printf("---[TimeWatcher Test Start]--- \n");
  

  while(1) {
      TimeWatcher t = createTimeWatcher();
      t->start();
      sleep(5);
      //t->stop();
      long interval = t->stop();
      if(interval != 5000) {
          printf("---[TimeWatcher Test {start/stop()} case1] [FAIL]--- \n");
          break;
      }

      printf("---[TimeWatcher Test {start/stop()} case1] [Success]--- \n");
      break;
  }
  

}
