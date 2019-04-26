#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "System.hpp"

using namespace obotcha;

#define CPU_NUMS 12

int main() {
  printf("---[System Test Start]--- \n");
  //static long int currentTimeMillis();
  while(1) {
    long int times = st(System)::currentTimeMillis();
    printf("System Test times is %ld \n",times);
    break;
  }

  //static int availableProcessors();
  while(1) {
    int num = st(System)::availableProcessors();
    if(num != CPU_NUMS) {
        printf("System availableProcessors test1-------[FAIL] \n");
        break;
    }

    printf("System availableProcessors test1-------[OK] \n");
    break;
  }

  //static int onlineProcessors();
  while(1) {
    int num = st(System)::onlineProcessors();
    if(num != CPU_NUMS) {
        printf("System Test test1-------[FAIL] \n");
        break;
    }

    printf("System Test test1-------[OK] \n");
    break;
  }

  //String executeForResult(String cmd);
  while(1) {
    String cmd = "ls -la";
    String result = st(System)::executeForResult(cmd);
    if(result->size() < 10) {
      printf("System executeForResult test1-------[FAIL] \n");
      break;
    }

    printf("System executeForResult test1-------[OK] \n");
    break;
  }

  //String execute
  while(1) {
      String cmd = "mkdir abc";
      st(System)::execute(cmd);
      printf("System execute test1-------[OK] \n");
      break;
  }

  //while(1){}
}
