#ifndef __EXECUTOR_SERVICE_H__
#define __EXECUTOR_SERVICE_H__

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

namespace obotcha {

DECLARE_SIMPLE_CLASS(ExecutorService) IMPLEMENTS(Executor) {

public:
    virtual void execute(Runnable command) = 0;

    //can not submit runnable,but we need wati all the 
    //runnable function complete
    virtual void shutdown() = 0;

    //close all thread directly
    virtual void shutdownNow() = 0;

    //if this executor has been shut down
    virtual bool isShutdown() = 0;

    //if all tasks have completed following shut down
    virtual bool isTerminated() = 0;

    //blocks until all tasks have completed execution after a shutdown
    virtual bool awaitTermination(long timeout) = 0;

    //virtual Future submit(Runnable task) = 0;
    virtual Future submit(Runnable task) = 0;
};

}
#endif