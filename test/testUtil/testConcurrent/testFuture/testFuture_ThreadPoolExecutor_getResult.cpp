#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ExecutorBuilder.hpp"
#include "Integer.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "Math.hpp"
#include "TaskResult.hpp"

using namespace obotcha;

DECLARE_CLASS(MyResult) {
public:
  int value1;
  long value2;
};

DECLARE_CLASS(RunTestObject) IMPLEMENTS(Runnable) {
public:
    void run() {
        MyResult r = createMyResult();
        r->value1 = 100;
        r->value2 = 123;
        st(TaskResult)::set(r);
    }
};

DECLARE_CLASS(RunTestInt) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(TaskResult)::set(1);
    }
};

DECLARE_CLASS(RunTestByte) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(TaskResult)::set((byte)2);
    }
};

DECLARE_CLASS(RunTestDouble) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(TaskResult)::set(3.3);
    }
};

DECLARE_CLASS(RunTestBoolFalse) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(TaskResult)::set(false);
    }
};

DECLARE_CLASS(RunTestBoolTrue) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(TaskResult)::set(true);
    }
};


DECLARE_CLASS(RunTestLong) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(TaskResult)::set((long)400);
    }
};

DECLARE_CLASS(RunTestUint16) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(TaskResult)::set((uint16_t)5);
    }
};

DECLARE_CLASS(RunTestUint32) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(TaskResult)::set((uint32_t)6);
    }
};

DECLARE_CLASS(RunTestUint64) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(TaskResult)::set((uint64_t)7);
    }
};

DECLARE_CLASS(RunTestString) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(TaskResult)::set(createString("hello world"));
    }
};

//delay Thread
DECLARE_CLASS(RunTestObjectDelayed) IMPLEMENTS(Runnable) {
public:
    void run() {
        MyResult r = createMyResult();
        r->value1 = 100;
        r->value2 = 123;
        st(TaskResult)::set(r);
        sleep(1);
    }
};

DECLARE_CLASS(RunTestIntDelayed) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(TaskResult)::set(1);
        sleep(1);
    }
};

DECLARE_CLASS(RunTestByteDelayed) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(TaskResult)::set((byte)2);
        sleep(1);
    }
};

DECLARE_CLASS(RunTestDoubleDelayed) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(TaskResult)::set(3.3);
        sleep(1);
    }
};

DECLARE_CLASS(RunTestBoolFalseDelayed) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(TaskResult)::set(false);
        sleep(1);
    }
};

DECLARE_CLASS(RunTestBoolTrueDelayed) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(TaskResult)::set(true);
        sleep(1);
    }
};


DECLARE_CLASS(RunTestLongDelayed) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(TaskResult)::set((long)400);
        sleep(1);
    }
};

DECLARE_CLASS(RunTestUint16Delayed) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(TaskResult)::set((uint16_t)5);
        sleep(1);
    }
};

DECLARE_CLASS(RunTestUint32Delayed) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(TaskResult)::set((uint32_t)6);
        sleep(1);
    }
};

DECLARE_CLASS(RunTestUint64Delayed) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(TaskResult)::set((uint64_t)7);
        sleep(1);
    }
};

DECLARE_CLASS(RunTestStringDelayed) IMPLEMENTS(Runnable) {
public:
    void run() {
        st(TaskResult)::set(createString("hello world"));
        sleep(1);
    }
};

DECLARE_CLASS(RunTestSleep10) IMPLEMENTS(Runnable) {
public:
    void run() {
        try {
          st(Thread)::msleep(10*1000);
        } catch(...) {}

    }
};

void testThreadPoolExecutor_GetResult() {
  //simple test case1
  while(1) {
    auto pool = createExecutorBuilder()->newThreadPool();
    RunTestObject objRun = createRunTestObject();
    Future f1 = pool->submit(objRun);
    MyResult r1 = f1->getResult<MyResult>();
    if(r1 == nullptr || r1->value1 != 100 || r1->value2 != 123) {
      printf("---[Future ThreadPoolExecutor GetResult case1 -------[FAIL] \n");
      break;
    }

    //int
    RunTestInt intRun = createRunTestInt();
    Future f2 = pool->submit(intRun);
    int r2 = f2->getResult<int>();

    if(r2 != 1) {
      printf("---[Future ThreadPoolExecutor GetResult case2 -------[FAIL] \n");
      break;
    }

    //byte
    RunTestByte byteRun = createRunTestByte();
    Future f3 = pool->submit(byteRun);
    byte r3 = f3->getResult<byte>();

    if(r3 != 2) {
      printf("---[Future ThreadPoolExecutor GetResult case3 -------[FAIL] \n");
      break;
    }

    //double
    RunTestDouble doubleRun = createRunTestDouble();
    Future f4 = pool->submit(doubleRun);
    double r4 = f4->getResult<double>();

    if(r4 != 3.3) {
      printf("---[Future ThreadPoolExecutor GetResult case4 -------[FAIL] \n");
      break;
    }

    //bool false
    RunTestBoolFalse falseRun = createRunTestBoolFalse();
    Future f5 = pool->submit(falseRun);
    bool r5 = f5->getResult<bool>();

    if(r5) {
      printf("---[Future ThreadPoolExecutor GetResult case5 -------[FAIL] \n");
      break;
    }

    //bool true
    RunTestBoolTrue trueRun = createRunTestBoolTrue();
    Future f6 = pool->submit(trueRun);
    bool r6 = f6->getResult<bool>();

    if(!r6) {
      printf("---[Future ThreadPoolExecutor GetResult case6 -------[FAIL] \n");
      break;
    }

    //long
    RunTestLong longRun = createRunTestLong();
    Future f7 = pool->submit(longRun);
    long r7 = f7->getResult<long>();

    if(r7 != 400) {
      printf("---[Future ThreadPoolExecutor GetResult case7 -------[FAIL] \n");
      break;
    }

    //uint16_t
    RunTestUint16 uint16Run = createRunTestUint16();
    Future f8 = pool->submit(uint16Run);
    uint16_t r8 = f8->getResult<uint16_t>();

    if(r8 != 5) {
      printf("---[Future ThreadPoolExecutor GetResult case8 -------[FAIL] \n");
      break;
    }

    //uint32_t
    RunTestUint32 uint32Run = createRunTestUint32();
    Future f9 = pool->submit(uint32Run);
    uint32_t r9 = f9->getResult<uint32_t>();

    if(r9 != 6) {
      printf("---[Future ThreadPoolExecutor GetResult case9 -------[FAIL] \n");
      break;
    }

    //uint64_t
    RunTestUint64 uint64Run = createRunTestUint64();
    Future f10 = pool->submit(uint64Run);
    uint64_t r10 = f10->getResult<uint64_t>();

    if(r10 != 7) {
      printf("---[Future ThreadPoolExecutor GetResult case10 -------[FAIL] \n");
      break;
    }

    //String
    RunTestString stringRun = createRunTestString();
    Future f11 = pool->submit(stringRun);
    String r11 = f11->getResult<String>();

    if(r11 == nullptr || !r11->equals("hello world")) {
      printf("---[Future ThreadPoolExecutor GetResult case11 -------[FAIL] \n");
      break;
    }

    pool->shutdown();

    printf("---[Future ThreadPoolExecutor GetResult case12 -------[OK] \n");
    break;
  }

  //simple test wait
  while(1) {
    auto pool = createExecutorBuilder()->newThreadPool();
    RunTestObjectDelayed objRun = createRunTestObjectDelayed();
    Future f1 = pool->submit(objRun);
    long int start = st(System)::currentTimeMillis();
    MyResult r1 = f1->getResult<MyResult>();
    long int internal = st(System)::currentTimeMillis() - start;
    if(internal > 1005 || internal < 905) {
      printf("---[Future ThreadPoolExecutor GetResult case13 -------[FAIL] \n");
      break;
    }

    if(r1 == nullptr || r1->value1 != 100 || r1->value2 != 123) {
      printf("---[Future ThreadPoolExecutor GetResult case14 -------[FAIL] \n");
      break;
    }

    //int
    RunTestIntDelayed intRun = createRunTestIntDelayed();
    Future f2 = pool->submit(intRun);
    //int r2 = f2->getResult<int>();
    start = st(System)::currentTimeMillis();
    int r2 = f2->getResult<int>();
    internal = st(System)::currentTimeMillis() - start;
    if(internal > 1005 || internal < 905) {
      printf("---[Future ThreadPoolExecutor GetResult case15 -------[FAIL],internal is %ld \n",internal);
      break;
    }

    if(r2 != 1) {
      printf("---[Future ThreadPoolExecutor GetResult case16 -------[FAIL] \n");
      break;
    }

    //byte
    RunTestByteDelayed byteRun = createRunTestByteDelayed();
    Future f3 = pool->submit(byteRun);
    //byte r3 = f3->getResult<byte>();
    start = st(System)::currentTimeMillis();
    byte r3 = f3->getResult<byte>();
    internal = st(System)::currentTimeMillis() - start;
    if(internal > 1005 || internal < 905) {
      printf("---[Future ThreadPoolExecutor GetResult case17 -------[FAIL] \n");
      break;
    }

    if(r3 != 2) {
      printf("---[Future ThreadPoolExecutor GetResult case18 -------[FAIL] \n");
      break;
    }

    //double
    RunTestDoubleDelayed doubleRun = createRunTestDoubleDelayed();
    Future f4 = pool->submit(doubleRun);
    //double r4 = f4->getResult<double>();
    start = st(System)::currentTimeMillis();
    double r4 = f4->getResult<double>();
    internal = st(System)::currentTimeMillis() - start;
    if(internal > 1005 || internal < 905) {
      printf("---[Future ThreadPoolExecutor GetResult case19 -------[FAIL] \n");
      break;
    }

    if(r4 != 3.3) {
      printf("---[Future ThreadPoolExecutor GetResult case20 -------[FAIL] \n");
      break;
    }

    //bool false
    RunTestBoolFalseDelayed falseRun = createRunTestBoolFalseDelayed();
    Future f5 = pool->submit(falseRun);
    //bool r5 = f5->getResult<bool>();
    start = st(System)::currentTimeMillis();
    bool r5 = f5->getResult<bool>();
    internal = st(System)::currentTimeMillis() - start;
    if(internal > 1005 || internal < 905) {
      printf("---[Future ThreadPoolExecutor GetResult case21 -------[FAIL] \n");
      break;
    }

    if(r5) {
      printf("---[Future ThreadPoolExecutor GetResult case22 -------[FAIL] \n");
      break;
    }

    //bool true
    RunTestBoolTrueDelayed trueRun = createRunTestBoolTrueDelayed();
    Future f6 = pool->submit(trueRun);
    //bool r6 = f6->getResult<bool>();
    start = st(System)::currentTimeMillis();
    bool r6 = f6->getResult<bool>();
    internal = st(System)::currentTimeMillis() - start;
    if(internal > 1005 || internal < 905) {
      printf("---[Future ThreadPoolExecutor GetResult case23 -------[FAIL] \n");
      break;
    }

    if(!r6) {
      printf("---[Future ThreadPoolExecutor GetResult case24 -------[FAIL] \n");
      break;
    }

    //long
    RunTestLongDelayed longRun = createRunTestLongDelayed();
    Future f7 = pool->submit(longRun);
    //long r7 = f7->getResult<long>();
    start = st(System)::currentTimeMillis();
    long r7 = f7->getResult<long>();
    internal = st(System)::currentTimeMillis() - start;
    if(internal > 1005 || internal < 905) {
      printf("---[Future ThreadPoolExecutor GetResult case25 -------[FAIL] \n");
      break;
    }

    if(r7 != 400) {
      printf("---[Future ThreadPoolExecutor GetResult case26 -------[FAIL] \n");
      break;
    }

    //uint16_t
    RunTestUint16Delayed uint16Run = createRunTestUint16Delayed();
    Future f8 = pool->submit(uint16Run);
    //uint16_t r8 = f8->getResult<uint16_t>();
    start = st(System)::currentTimeMillis();
    uint16_t r8 = f8->getResult<uint16_t>();
    internal = st(System)::currentTimeMillis() - start;
    if(internal > 1005 || internal < 905) {
      printf("---[Future ThreadPoolExecutor GetResult case27 -------[FAIL] \n");
      break;
    }

    if(r8 != 5) {
      printf("---[Future ThreadPoolExecutor GetResult case28 -------[FAIL] \n");
      break;
    }

    //uint32_t
    RunTestUint32Delayed uint32Run = createRunTestUint32Delayed();
    Future f9 = pool->submit(uint32Run);
    //uint32_t r9 = f9->getResult<uint32_t>();
    start = st(System)::currentTimeMillis();
    uint32_t r9 = f9->getResult<uint32_t>();
    internal = st(System)::currentTimeMillis() - start;
    if(internal > 1005 || internal < 905) {
      printf("---[Future ThreadPoolExecutor GetResult case29 -------[FAIL] \n");
      break;
    }

    if(r9 != 6) {
      printf("---[Future ThreadPoolExecutor GetResult case30 -------[FAIL] \n");
      break;
    }

    //uint64_t
    RunTestUint64Delayed uint64Run = createRunTestUint64Delayed();
    Future f10 = pool->submit(uint64Run);
    //uint32_t r10 = f10->getResult<uint64_t>();
    start = st(System)::currentTimeMillis();
    uint64_t r10 = f10->getResult<uint64_t>();
    internal = st(System)::currentTimeMillis() - start;
    if(internal > 1005 || internal < 905) {
      printf("---[Future ThreadPoolExecutor GetResult case31 -------[FAIL] \n");
      break;
    }

    if(r10 != 7) {
      printf("---[Future ThreadPoolExecutor GetResult case32 -------[FAIL] \n");
      break;
    }

    //String
    RunTestStringDelayed stringRun = createRunTestStringDelayed();
    Future f11 = pool->submit(stringRun);
    //String r11 = f11->getResult<String>();
    start = st(System)::currentTimeMillis();
    String r11 = f11->getResult<String>();
    internal = st(System)::currentTimeMillis() - start;
    if(internal > 1005 || internal < 905) {
      printf("---[Future ThreadPoolExecutor GetResult case33 -------[FAIL] \n");
      break;
    }

    if(r11 == nullptr || !r11->equals("hello world")) {
      printf("---[Future ThreadPoolExecutor GetResult case34 -------[FAIL] \n");
      break;
    }

    pool->shutdown();

    printf("---[Future ThreadPoolExecutor GetResult case35 -------[OK] \n");
    break;
  }

  //test cancel
  while(1) {
    auto pool = createExecutorBuilder()->setThreadNum(1)->newThreadPool();
    pool->submit(createRunTestSleep10());
    bool isException = false;

    RunTestObject objRun = createRunTestObject();
    Future f1 = pool->submit(objRun);
    Thread t = createThread([&f1]{
      usleep(100);
      f1->cancel();
    });
    t->start();

    try {
      MyResult r1 = f1->getResult<MyResult>();
    } catch(...) {
      isException = true;
    }

    if(!isException) {
      printf("---[Future ThreadPoolExecutor GetResult case36 -------[FAIL] \n");
      break;
    }

    //int
    RunTestInt intRun = createRunTestInt();
    Future f2 = pool->submit(intRun);
    isException = false;
    t = createThread([&f2]{
      usleep(100);
      f2->cancel();
    });
    t->start();

    try {
      int r2 = f2->getResult<int>();
    } catch(...) {
      isException = true;
    }

    if(!isException) {
      printf("---[Future ThreadPoolExecutor GetResult case37 -------[FAIL] \n");
      break;
    }

    //byte
    RunTestByte byteRun = createRunTestByte();
    Future f3 = pool->submit(byteRun);
    isException = false;
    t = createThread([&f3]{
      usleep(100);
      f3->cancel();
    });
    t->start();
    try {
      byte r3 = f3->getResult<byte>();
    } catch(...) {
      isException = true;
    }


    if(!isException) {
      printf("---[Future ThreadPoolExecutor GetResult case38 -------[FAIL] \n");
      break;
    }

    //double
    RunTestDouble doubleRun = createRunTestDouble();
    Future f4 = pool->submit(doubleRun);
    //double r4 = f4->getResult<double>();
    isException = false;
    t = createThread([&f4]{
      usleep(100);
      f4->cancel();
    });
    t->start();
    try {
      double r4 = f4->getResult<double>();
    } catch(...) {
      isException = true;
    }

    if(!isException) {
      printf("---[Future ThreadPoolExecutor GetResult case39 -------[FAIL] \n");
      break;
    }

    //bool false
    RunTestBoolFalse falseRun = createRunTestBoolFalse();
    Future f5 = pool->submit(falseRun);
    //bool r5 = f5->getResult<bool>();
    isException = false;
    t = createThread([&f5]{
      usleep(100);
      f5->cancel();
    });
    t->start();
    try {
      bool r5 = f5->getResult<bool>();
    } catch(...) {
      isException = true;
    }

    if(!isException) {
      printf("---[Future ThreadPoolExecutor GetResult case40 -------[FAIL] \n");
      break;
    }

    //bool true
    RunTestBoolTrue trueRun = createRunTestBoolTrue();
    Future f6 = pool->submit(trueRun);
    //bool r6 = f6->getResult<bool>();
    isException = false;
    t = createThread([&f6]{
      usleep(100);
      f6->cancel();
    });
    t->start();
    try {
      bool r6 = f6->getResult<bool>();
    } catch(...) {
      isException = true;
    }

    if(!isException) {
      printf("---[Future ThreadPoolExecutor GetResult case41 -------[FAIL] \n");
      break;
    }

    //long
    RunTestLong longRun = createRunTestLong();
    Future f7 = pool->submit(longRun);
    //long r7 = f7->getResult<long>();
    isException = false;
    t = createThread([&f7]{
      usleep(100);
      f7->cancel();
    });
    t->start();
    try {
      long r7 = f7->getResult<long>();
    } catch(...) {
      isException = true;
    }

    if(!isException) {
      printf("---[Future ThreadPoolExecutor GetResult case42 -------[FAIL] \n");
      break;
    }

    //uint16_t
    RunTestUint16 uint16Run = createRunTestUint16();
    Future f8 = pool->submit(uint16Run);
    //uint16_t r8 = f8->getResult<uint16_t>();
    isException = false;
    t = createThread([&f8]{
      usleep(100);
      f8->cancel();
    });

    t->start();
    try {
      uint16_t r8 = f8->getResult<uint16_t>();
    } catch(...) {
      isException = true;
    }

    if(!isException) {
      printf("---[Future ThreadPoolExecutor GetResult case43 -------[FAIL] \n");
      break;
    }

    //uint32_t
    RunTestUint32 uint32Run = createRunTestUint32();
    Future f9 = pool->submit(uint32Run);
    //uint32_t r9 = f9->getResult<uint32_t>();
    isException = false;
    t = createThread([&f9]{
      usleep(100);
      f9->cancel();
    });

    t->start();
    try {
      uint32_t r9 = f9->getResult<uint32_t>();
    } catch(...) {
      isException = true;
    }

    if(!isException) {
      printf("---[Future ThreadPoolExecutor GetResult case44 -------[FAIL] \n");
      break;
    }

    //uint64_t
    RunTestUint64 uint64Run = createRunTestUint64();
    Future f10 = pool->submit(uint64Run);
    //uint64_t r10 = f10->getResult<uint64_t>();
    isException = false;
    t = createThread([&f10]{
      usleep(100);
      f10->cancel();
    });

    t->start();
    try {
      uint64_t r10 = f10->getResult<uint64_t>();
    } catch(...) {
      isException = true;
    }

    if(!isException) {
      printf("---[Future ThreadPoolExecutor GetResult case45 -------[FAIL] \n");
      break;
    }

    //String
    RunTestString stringRun = createRunTestString();
    Future f11 = pool->submit(stringRun);
    //String r11 = f11->getResult<String>();
    isException = false;
    t = createThread([&f11]{
      usleep(100);
      f11->cancel();
    });

    t->start();
    try {
      String r11 = f11->getResult<String>();
    } catch(...) {
      isException = true;
    }

    if(!isException) {
      printf("---[Future ThreadPoolExecutor GetResult case46 -------[FAIL] \n");
      break;
    }
    pool->shutdown();
    pool->awaitTermination();

    printf("---[Future ThreadPoolExecutor GetResult case47 -------[OK] \n");
    break;
  }

  printf("---[Future ThreadPoolExecutor GetResult case100 -------[OK] \n");
}
