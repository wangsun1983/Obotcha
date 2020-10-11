#ifndef __OBOTCHA_EXECUTOR_SERVICE_H__
#define __OBOTCHA_EXECUTOR_SERVICE_H__

#include <pthread.h>
#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Runnable.hpp"
#include "Executor.hpp"
#include "ArrayList.hpp"
#include "Future.hpp"
#include "Executor.hpp"
#include "Callable.hpp"
#include "AutoClose.hpp"
#include "Condition.hpp"
#include "Thread.hpp"

namespace obotcha {

enum ExecutorState {
    idleState,
    busyState,
    terminateState,
    illegalState,
};

class _ExecutorService;

DECLARE_SIMPLE_CLASS(ExecutorServiceListener) {
public:
    virtual void onTerminate(sp<_ExecutorService>) = 0;
};

DECLARE_SIMPLE_CLASS(ExecutorService) IMPLEMENTS(Executor) {

public:
    virtual int execute(Runnable command) = 0;

    virtual int execute(int,Runnable){return 0;};
    
    //can not submit runnable,but we need wati all the 
    //runnable function complete
    virtual int shutdown() = 0;

    //close all thread directly
    //virtual int shutdownNow() = 0;

    //if this executor has been shut down
    //virtual bool isShutdown() = 0;

    //update status as terminate
    virtual void setAsTerminated() = 0;
    
    //if all tasks have completed following shut down
    virtual bool isTerminated() = 0;

    //blocks until all tasks have completed execution after a shutdown
    virtual int awaitTermination(long timeout) = 0;

    //wait for thread pool terminatin
    virtual void awaitTermination() = 0;

    //virtual Future submit(Runnable task) = 0;
    virtual Future submit(Runnable task) = 0;

    virtual Future submit(int,Runnable){return nullptr;};

    //get thread num
    virtual int getThreadsNum() = 0;
    
};

}
#endif