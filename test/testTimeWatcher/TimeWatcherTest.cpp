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
  
  TimeWatcher t = createTimeWatcher();
  t->start();
  sleep(2);
  printf("cost : %ld \n",t->stop());

  {
    startAutoTimeWatcher("MyTest");
    sleep(3);
  }

  while(1){}

}
