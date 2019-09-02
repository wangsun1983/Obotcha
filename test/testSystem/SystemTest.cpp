#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "System.hpp"
#include "File.hpp"

using namespace obotcha;

#define CPU_NUMS 12

int main() {
  printf("---[System Test Start]--- \n");
  //static long int currentTimeMillis();
  while(1) {
    long int times = st(System)::currentTimeMillis();
    if(times <= 0) {
      printf("System currentTimeMillis test1-------[FAIL] \n");
      break;
    }
    
    printf("System currentTimeMillis test1-------[Success] \n");
      break;
    break;
  }

  //static int availableProcessors();
  while(1) {
    int num = st(System)::availableProcessors();
    if(num != CPU_NUMS) {
        printf("System availableProcessors test1-------[FAIL] \n");
        break;
    }

    printf("System availableProcessors test1-------[Success] \n");
    break;
  }

  //static int onlineProcessors();
  while(1) {
    int num = st(System)::onlineProcessors();
    if(num != CPU_NUMS) {
        printf("System Test test1-------[FAIL] \n");
        break;
    }

    printf("System Test test1-------[Success] \n");
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

    printf("System executeForResult test1-------[Success] \n");
    break;
  }

  //String execute
  while(1) {
      File file = createFile("abc");
      if(file->exists()) {
        file->removeAll();
      }

      if(file->exists()) {
        printf("System execute test1-------[FAIL] \n");
        break;
      }

      String cmd = "mkdir abc";
      st(System)::execute(cmd);
      if(!file->exists()) {
        printf("System execute test2-------[FAIL] \n");
        break;
      }

      printf("System execute test1-------[Success] \n");
      break;
  }

  //while(1){}
}
