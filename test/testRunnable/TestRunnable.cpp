#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "Long.hpp"
#include "UUID.hpp"
#include "Log.hpp"
#include "ArrayList.hpp"
#include "String.hpp"
#include "Runnable.hpp"
#include "ExecutorService.hpp"
#include "Executors.hpp"
#include "Condition.hpp"
#include "Mutex.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyData) {
public:
    int value;    
};

DECLARE_SIMPLE_CLASS(MyRun) IMPLEMENTS(Runnable) {
public:
    _MyRun() {
        printf("myRun \n");
    }

    void run() {
        printf("start run \n");
        //sleep(100);
        Condition cond = createCondition();
        Mutex mutex = createMutex();
        printf("finish sleep,set result1 \n");
        AutoLock l(mutex);
        cond->wait(mutex,100000);
        printf("finish sleep,set result2 \n");
        MyData data = createMyData();
        data->value = 199;
        setResult(data);
        printf("run complete \n");
    }
};

DECLARE_SIMPLE_CLASS(CancelTask) IMPLEMENTS(Runnable) {
public:
    _CancelTask(Future f) {
        task = f;
    }

    void run() {
        printf("start cancel \n");
        sleep(10);
        printf("start i want cancle \n");
        task->cancel();
    }

private:
    Future task;
};


int main() {
    ExecutorService pool = st(Executors)::newFixedThreadPool(2,2);
    Future future = pool->submit(createMyRun());
    pool->submit(createCancelTask(future));
    try {
        MyData value = future->getResult<MyData>();
        printf("result is %d \n",value->value);
    } catch(InterruptedException &e) {
        printf("exception !!!!! \n");
    }
    pool->shutdown();
}
