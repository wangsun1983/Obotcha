#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "CountDownLatch.hpp"
#include "Thread.hpp"

DECLARE_SIMPLE_CLASS(MyThread1) IMPLEMENTS(Thread) {
public:
  _MyThread1(CountDownLatch lat) {
    latch = lat;
  }

  void run() {
      printf("start sleep \n");
      st(Thread)::msleep(8000);
      latch->countDown();
      printf("start sleep end\n");
  }

private:
  CountDownLatch latch;
};

int main() {
    CountDownLatch latch = createCountDownLatch(1);
    MyThread1 t1 = createMyThread1(latch);

    t1->start();
    printf("start wait \n");
    latch->await(1000*15);
    printf("wait complete \n");
}
