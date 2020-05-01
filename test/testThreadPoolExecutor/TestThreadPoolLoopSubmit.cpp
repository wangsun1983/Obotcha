#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Mutex.hpp"
#include "AutoMutex.hpp"
#include "System.hpp"
#include "ThreadPoolExecutor.hpp"
#include "Error.hpp"
#include "AtomicInteger.hpp"

using namespace obotcha;

AtomicInteger value = createAtomicInteger(0);

DECLARE_SIMPLE_CLASS(MyLoopSubmitRunnable1) IMPLEMENTS(Runnable) {
public:
    void run() {
        value->incrementAndGet();
    }

    void onInterrupt() {
    }
};

DECLARE_SIMPLE_CLASS(MyLoopSubmitRunnable2) IMPLEMENTS(Runnable) {
public:
    void run() {
        value->decrementAndGet();
    }

    void onInterrupt() {
    }
};

int testThreadPoolLoopSubmit() {
    //test1
    ThreadPoolExecutor executor = createThreadPoolExecutor(4,4);
    for(int i = 0;i<1024*8;i++){
      executor->execute(createMyLoopSubmitRunnable1());
    }

    sleep(1);
    if(value->get() != 1024*8) {
      printf("---[ThreadPoolExecutor Loop Submit} special case1] [FAIL]--- \n");
    }

    //test2
    ThreadPoolExecutor executor2 = createThreadPoolExecutor(4,4);
    for(int i = 0;i<1024*8;i++){
      executor->submit(createMyLoopSubmitRunnable2());
    }

    sleep(1);
    if(value->get() != 0) {
      printf("---[ThreadPoolExecutor Loop Submit} special case2] [FAIL]--- \n");
    }


    printf("---[ThreadPoolExecutor Loop Submit} special case100] [OK]--- \n");

    return 0;

}
