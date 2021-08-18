#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ExecutorService.hpp"
#include "Integer.hpp"
#include "Executors.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "Math.hpp"

using namespace obotcha;

DECLARE_CLASS(WrongObjectData) {
public:
  int value1;
  int value2;
};

DECLARE_CLASS(TestWrongIntTask) IMPLEMENTS(Runnable){
public:
  void run() {
    byte value = 10;
    this->setResult(value);
  }
};

DECLARE_CLASS(TestWrongObjectTask) IMPLEMENTS(Runnable){
public:
  void run() {
    WrongObjectData obj = createWrongObjectData();
    obj->value1 = 1;
    obj->value2 = 2;
    this->setResult(obj);
  }
};

int testThreadExecutorPoolWrongResult() {
    ExecutorService pool = st(Executors)::newFixedThreadPool(1);
    //case1
    while(1) {
      TestWrongIntTask task = createTestWrongIntTask();
      Future f1 = pool->submit(task);
      sleep(1);
      int value = f1->getResult(-1);
      if(value != 10) {
        printf("testThreadExecutorPoolWrongResult value is %d case1 -------[FAIL] \n",value);
        break;
      }

      long value2 = f1->getResult(-1);
      if(value2 != 10) {
        printf("testThreadExecutorPoolWrongResult case2 -------[FAIL] \n");
        break;
      }

      uint16_t value3 = f1->getResult(-1);
      if(value3 != 10) {
        printf("testThreadExecutorPoolWrongResult case3 -------[FAIL] \n");
        break;
      }

      uint32_t value4 = f1->getResult(-1);
      if(value4 != 10) {
        printf("testThreadExecutorPoolWrongResult case4 -------[FAIL] \n");
        break;
      }

      byte value5 = f1->getResult(-1);
      if(value5 != 10) {
        printf("testThreadExecutorPoolWrongResult case5 -------[FAIL] \n");
        break;
      }

      String value6 = f1->getResult(NullData<String>());
      if(value6 != nullptr) {
        printf("testThreadExecutorPoolWrongResult case6 -------[FAIL] \n");
        break;
      }

      printf("testThreadExecutorPoolWrongResult case6 -------[OK] \n");
      break;
    }

    while(1) {
      TestWrongObjectTask task = createTestWrongObjectTask();
      Future f1 = pool->submit(task);
      int value = f1->getResult(-10);
      if(value != -10) {
        printf("testThreadExecutorPoolWrongResult value is %d case7 -------[FAIL] \n",value);
        break;
      }

      printf("testThreadExecutorPoolWrongResult case10 -------[OK] \n");
      break;
    }

    pool->shutdown();
}
