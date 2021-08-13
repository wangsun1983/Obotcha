#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "CountDownLatch.hpp"
#include "Thread.hpp"
#include "System.hpp"

using namespace obotcha;

void testCountDownLatch_Construct() {
    while(1) {
      bool isException  = false;
      try {
        CountDownLatch l = createCountDownLatch(0);
      } catch(...) {
        isException = true;
      }

      if(!isException) {
        printf("---[TestCountDownLatch Construct case1] [FAILED]--- \n");
        break;
      }

      break;
    }

    printf("---[TestCountDownLatch Construct case100] [OK]--- \n");
}
