#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"

int main() {
  printf("---[System Test Start]--- \n");
  //Test void start();
  {
    printf("cpu total num is %d \n",st(System)::availableProcessors());
    printf("cpu online num is %d \n",st(System)::onlineProcessors());
  }

  //while(1){}
}
