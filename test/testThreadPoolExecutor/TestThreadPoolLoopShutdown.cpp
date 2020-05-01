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

AtomicInteger interruptCount = createAtomicInteger(0);

DECLARE_SIMPLE_CLASS(MyLoopShutdownRunnable1) IMPLEMENTS(Runnable) {
public:
    void run() {
        sleep(100);
    }

    void onInterrupt() {
      interruptCount->incrementAndGet();
    }
};

int testThreadPoolLoopShutdown() {
    //test1
    ThreadPoolExecutor executor = createThreadPoolExecutor(8*1024,4);
    for(int i = 0;i<1024*8;i++){
      int v=executor->execute(createMyLoopShutdownRunnable1());
    }

    int ret = executor->shutdown();
    printf("ret is %d \n",ret);

    executor->awaitTermination();

    if(interruptCount->get() != 1024*8) {
      printf("---[ThreadPoolExecutor Loop shutdown} special case1,value is %d] [FAIL]--- \n",interruptCount->get());
    }

    //test2
    interruptCount = createAtomicInteger(0);
    ThreadPoolExecutor executor2 = createThreadPoolExecutor(8*1024,4);
    ArrayList<Future> list = createArrayList<Future>();
    for(int i = 0;i<1024*8;i++){
      Future v = executor2->submit(createMyLoopShutdownRunnable1());
      list->add(v);
    }

    for(int i = 0;i<1024*8;i++) {
      Future v = list->get(i);
      v->cancel();
    }

    if(interruptCount->get() != 1024*8) {
      printf("---[ThreadPoolExecutor Loop shutdown} special case2,value is %d] [FAIL]--- \n",interruptCount->get());
    }

    printf("---[ThreadPoolExecutor Loop Submit} special case100] [OK]--- \n");

    return 0;

}
