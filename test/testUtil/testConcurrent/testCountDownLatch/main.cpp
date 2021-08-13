#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "CountDownLatch.hpp"
#include "Thread.hpp"
#include "System.hpp"

using namespace obotcha;

extern int normaltest();
extern int notifytest();
extern void testCountDownLatch_CountDown();
extern void testCountDownLatch_Construct();
extern void testCountDownLatch_Await();
extern void testCountDownLatch_MultiThread();

int main() {
    testCountDownLatch_CountDown();
    testCountDownLatch_Construct();
    testCountDownLatch_Await();
    testCountDownLatch_MultiThread();
}
