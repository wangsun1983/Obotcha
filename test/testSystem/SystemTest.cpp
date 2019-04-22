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
        printf("System availableProcessors test1-------[FAIL] \n",times);
        break;
    }

    printf("System availableProcessors test1-------[OK] \n",times);
    break;
  }

  //static int onlineProcessors();
  while(1) {
    int num = st(System)::onlineProcessors();
    if(num != CPU_NUMS) {
        printf("System Test test1-------[FAIL] \n",times);
        break;
    }

    printf("System Test test1-------[OK] \n",times);
    break;
  }

  //static void exit(int);




  {
    printf("cpu total num is %d \n",st(System)::availableProcessors());
    printf("cpu online num is %d \n",st(System)::onlineProcessors());
  }

  //while(1){}
}
