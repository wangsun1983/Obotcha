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

DECLARE_SIMPLE_CLASS(ResultData2) {
public:
  int value1;
  int value2;
};

DECLARE_SIMPLE_CLASS(ThreadPoolResultRunInt2) IMPLEMENTS(Runnable){
public:
  void run() {
    sleep(1);
    this->setResult(1);
  }
};

DECLARE_SIMPLE_CLASS(ThreadPoolResultRunByte2) IMPLEMENTS(Runnable){
public:
  void run() {
    sleep(1);
    this->setResult(1);
  }
};

DECLARE_SIMPLE_CLASS(ThreadPoolResultRunDouble2) IMPLEMENTS(Runnable){
public:
  void run() {
    sleep(1);
    this->setResult(1.1);
  }
};

DECLARE_SIMPLE_CLASS(ThreadPoolResultRunBool2) IMPLEMENTS(Runnable){
public:
  void run() {
    sleep(1);
    this->setResult(false);
  }
};

DECLARE_SIMPLE_CLASS(ThreadPoolResultRunFloat2) IMPLEMENTS(Runnable){
public:
  void run() {
    sleep(1);
    this->setResult(2.2);
  }
};

DECLARE_SIMPLE_CLASS(ThreadPoolResultRunLong2) IMPLEMENTS(Runnable){
public:
  void run() {
    sleep(1);
    this->setResult(4);
  }
};

DECLARE_SIMPLE_CLASS(ThreadPoolResultRunUint16_2) IMPLEMENTS(Runnable){
public:
  void run() {
    sleep(1);
    this->setResult(5);
  }
};

DECLARE_SIMPLE_CLASS(ThreadPoolResultRunUint32_2) IMPLEMENTS(Runnable){
public:
  void run() {
    sleep(1);
    this->setResult(6);
  }
};

DECLARE_SIMPLE_CLASS(ThreadPoolResultRunUint64_2) IMPLEMENTS(Runnable){
public:
  void run() {
    sleep(1);
    this->setResult(7);
  }
};

DECLARE_SIMPLE_CLASS(ThreadPoolResultRunString2) IMPLEMENTS(Runnable){
public:
  void run() {
    sleep(1);
    this->setResult(createString("hello"));
  }
};

DECLARE_SIMPLE_CLASS(ThreadPoolResultRunObject2) IMPLEMENTS(Runnable){
public:
  void run() {
    ResultData2 r1 = createResultData2();
    r1->value1 = 10;
    r1->value2 = 20;
    sleep(1);
    this->setResult(r1);
  }
};

int testThreadExecutorPoolFutureResultDelay() {

    while(1) {
        ExecutorService pool = st(Executors)::newFixedThreadPool(1);
        ThreadPoolResultRunInt2 intRun = createThreadPoolResultRunInt2();
        Future f = pool->submit(intRun);
        long trace1 = st(System)::currentTimeMillis();
        int ret1 = f->getResult(-1);
        long interval = st(System)::currentTimeMillis() - trace1;

        if(ret1 != 1) {
          printf("testThreadExecutorPoolFutureResultDelay case1 -------[FAIL] \n");
          break;
        }

        if(interval > 1010 || interval < 999) {
          printf("testThreadExecutorPoolFutureResultDelay case2 -------[FAIL] \n");
          break;
        }

        ThreadPoolResultRunByte2 byteRun = createThreadPoolResultRunByte2();
        f = pool->submit(byteRun);
        trace1 = st(System)::currentTimeMillis();
        byte ret2 = f->getResult(-1);
        interval = st(System)::currentTimeMillis() - trace1;
        if(ret2 != 1) {
          printf("testThreadExecutorPoolFutureResultDelay case3 -------[FAIL] \n");
          break;
        }

        if(interval > 1010 ||interval < 999) {
          printf("testThreadExecutorPoolFutureResultDelay case4 -------[FAIL] \n");
          break;
        }

        ThreadPoolResultRunDouble2 doubleRun = createThreadPoolResultRunDouble2();
        f = pool->submit(doubleRun);
        trace1 = st(System)::currentTimeMillis();
        double ret3 = f->getResult(-1.1);
        interval = st(System)::currentTimeMillis() - trace1;
        if(ret3 != 1.1) {
          printf("testThreadExecutorPoolFutureResultDelay case5 -------[FAIL] \n");
          break;
        }

        if(interval > 1010 ||interval < 999) {
          printf("testThreadExecutorPoolFutureResultDelay case6 -------[FAIL] \n");
          break;
        }

        ThreadPoolResultRunBool2 boolRun = createThreadPoolResultRunBool2();
        f = pool->submit(boolRun);
        trace1 = st(System)::currentTimeMillis();
        bool ret3_1 = f->getResult(-1.1);
        interval = st(System)::currentTimeMillis() - trace1;
        if(ret3_1 != false) {
          printf("testThreadExecutorPoolFutureResultDelay case7 -------[FAIL] \n");
          break;
        }

        if(interval > 1010 ||interval < 999) {
          printf("testThreadExecutorPoolFutureResultDelay case8 -------[FAIL] \n");
          break;
        }

        ThreadPoolResultRunFloat2 floatRun = createThreadPoolResultRunFloat2();
        f = pool->submit(floatRun);
        trace1 = st(System)::currentTimeMillis();
        float ret4 = f->getResult(-1.1);
        interval = st(System)::currentTimeMillis() - trace1;
        if(st(Math)::compareFloat(ret4,2.2) != st(Math)::CompareParamEqual) {
          printf("testThreadExecutorPoolFutureResultDelay case9 -------[FAIL] \n");
          break;
        }
        if(interval > 1010 ||interval < 999) {
          printf("testThreadExecutorPoolFutureResultDelay case10 -------[FAIL] \n");
          break;
        }

        ThreadPoolResultRunLong2 longRun = createThreadPoolResultRunLong2();
        f = pool->submit(longRun);
        trace1 = st(System)::currentTimeMillis();
        long ret5 = f->getResult(-1);
        interval = st(System)::currentTimeMillis() - trace1;
        if(ret5 != 4) {
          printf("testThreadExecutorPoolFutureResultDelay case11 -------[FAIL] \n");
          break;
        }

        if(interval > 1010 ||interval < 999) {
          printf("testThreadExecutorPoolFutureResultDelay case12 -------[FAIL] \n");
          break;
        }

        ThreadPoolResultRunUint16_2 uint16Run = createThreadPoolResultRunUint16_2();
        f = pool->submit(uint16Run);
        trace1 = st(System)::currentTimeMillis();
        uint16_t ret6 = f->getResult(1);
        interval = st(System)::currentTimeMillis() - trace1;
        if(ret6 != 5) {
          printf("testThreadExecutorPoolFutureResultDelay case13 -------[FAIL] \n");
          break;
        }
        if(interval > 1010 ||interval < 999) {
          printf("testThreadExecutorPoolFutureResultDelay case14 -------[FAIL] \n");
          break;
        }

        ThreadPoolResultRunUint32_2 uint32Run = createThreadPoolResultRunUint32_2();
        f = pool->submit(uint32Run);
        trace1 = st(System)::currentTimeMillis();
        uint32_t ret7 = f->getResult(1);
        interval = st(System)::currentTimeMillis() - trace1;
        if(ret7 != 6) {
          printf("testThreadExecutorPoolFutureResultDelay case15 -------[FAIL] \n");
          break;
        }
        if(interval > 1010 ||interval < 999) {
          printf("testThreadExecutorPoolFutureResultDelay case16 -------[FAIL] \n");
          break;
        }

        ThreadPoolResultRunUint64_2 uint64Run = createThreadPoolResultRunUint64_2();
        f = pool->submit(uint64Run);
        trace1 = st(System)::currentTimeMillis();
        uint64_t ret8 = f->getResult(1);
        interval = st(System)::currentTimeMillis() - trace1;
        if(ret8 != 7) {
          printf("testThreadExecutorPoolFutureResultDelay case17 -------[FAIL] \n");
          break;
        }
        if(interval > 1010 ||interval < 999) {
          printf("testThreadExecutorPoolFutureResultDelay case18 -------[FAIL] \n");
          break;
        }

        ThreadPoolResultRunString2 stringRun = createThreadPoolResultRunString2();
        f = pool->submit(stringRun);
        trace1 = st(System)::currentTimeMillis();
        String ret9 = f->getResult(NullData<String>());
        interval = st(System)::currentTimeMillis() - trace1;
        if(!ret9->equals("hello")) {
          printf("testThreadExecutorPoolFutureResultDelay case19 -------[FAIL] \n");
          break;
        }
        if(interval > 1010 ||interval < 999) {
          printf("testThreadExecutorPoolFutureResultDelay case20 -------[FAIL] \n");
          break;
        }

        ThreadPoolResultRunObject2 objRun = createThreadPoolResultRunObject2();
        f = pool->submit(objRun);
        trace1 = st(System)::currentTimeMillis();
        ResultData2 ret10 = f->getResult(NullData<ResultData2>());
        interval = st(System)::currentTimeMillis() - trace1;
        if(ret10 == nullptr || ret10->value1 != 10 ||ret10->value2 != 20) {
          printf("testThreadExecutorPoolFutureResultDelay case21 -------[FAIL] \n");
          break;
        }

        if(interval > 1010 ||interval < 999) {
          printf("testThreadExecutorPoolFutureResultDelay case22 -------[FAIL] \n");
          break;
        }

        printf("testThreadExecutorPoolFutureResultDelay case23 -------[OK] \n");
        break;
    }
}
