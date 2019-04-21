#ifndef __SCHEDULED_EXECUTOR_SERVICE_H__
#define __SCHEDULED_EXECUTOR_SERVICE_H__

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

DECLARE_SIMPLE_CLASS(ScheduledExecutorService) IMPLEMENTS(ExecutorService) {

public:
    virtual Future schedule(Runnable command,long delay) = 0;

    virtual Future scheduleAtFixedRate(Runnable command,
                                        long initialDelay,
                                        long period) = 0;

    virtual Future scheduleWithFixedDelay(Runnable command,
                                                     long initialDelay,
                                                     long delay) = 0;
};

}
#endif