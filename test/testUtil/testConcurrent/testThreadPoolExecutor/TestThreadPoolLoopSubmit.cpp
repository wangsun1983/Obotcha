#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Mutex.hpp"
#include "AutoLock.hpp"
#include "System.hpp"
#include "ThreadPoolExecutor.hpp"
#include "Error.hpp"
#include "AtomicInteger.hpp"

using namespace obotcha;

AtomicInteger value = createAtomicInteger(0);

DECLARE_CLASS(MyLoopSubmitRunnable1) IMPLEMENTS(Runnable) {
public:
    void run() {
        value->incrementAndGet();
    }

    void onInterrupt() {
    }
};

DECLARE_CLASS(MyLoopSubmitRunnable2) IMPLEMENTS(Runnable) {
public:
    void run() {
        value->decrementAndGet();
    }

    void onInterrupt() {
    }
};

DECLARE_CLASS(MyLoopSubmitRunnable3) IMPLEMENTS(Runnable) {
public:
    void run() {
        sleep(5);
    }

    void onInterrupt() {
    }
};

int testThreadPoolLoopSubmit() {
    printf("testThreadPoolLoopSubmit trace1 \n");
    //test1
    ThreadPoolExecutor executor = createThreadPoolExecutor(4,4);
    for(int i = 0;i<1024*8;i++){
      executor->execute(createMyLoopSubmitRunnable1());
    }
    printf("testThreadPoolLoopSubmit trace2 \n");
    sleep(1);
    if(value->get() != 1024*8) {
      printf("---[ThreadPoolExecutor Loop Submit} special case1] [FAIL]--- \n");
    }
    printf("testThreadPoolLoopSubmit trace3 \n");
    executor->shutdown();
    printf("testThreadPoolLoopSubmit trace4 \n");
    //test2
    ThreadPoolExecutor executor2 = createThreadPoolExecutor(4,4);
    for(int i = 0;i<1024*8;i++){
      executor2->submit(createMyLoopSubmitRunnable2());
    }
    printf("testThreadPoolLoopSubmit trace5 \n");
    sleep(1);
    if(value->get() != 0) {
      printf("---[ThreadPoolExecutor Loop Submit} special case2] value is %d [FAIL]--- \n",value->get());
    }
    executor2->shutdown();
    printf("testThreadPoolLoopSubmit trace6 \n");
    //test3
    ThreadPoolExecutor executor3 = createThreadPoolExecutor(1,1);
    executor3->submit(createMyLoopSubmitRunnable3());
    executor3->submit(createMyLoopSubmitRunnable3());
    long c = st(System)::currentTimeMillis();
    executor3->submit(createMyLoopSubmitRunnable3());
    long interval = st(System)::currentTimeMillis() - c;
    printf("testThreadPoolLoopSubmit trace7 \n");
    if(interval < 5000 || interval > 5005) {
      printf("---[ThreadPoolExecutor Loop Submit} special case3],interval is %ld [FAIL]--- \n",interval);
    }
    executor3->shutdown();
    printf("testThreadPoolLoopSubmit trace8 \n");
    printf("---[ThreadPoolExecutor Loop Submit} special case100] [OK]--- \n");

    return 0;

}
