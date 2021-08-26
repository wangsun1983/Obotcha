#ifndef __OBOTCHA_EXECUTOR_HPP__
#define __OBOTCHA_EXECUTOR_HPP__

#include "Mutex.hpp"
#include "Condition.hpp"
#include "Runnable.hpp"
#include "InterruptedException.hpp"
#include "TimeOutException.hpp"
#include "OStdInstanceOf.hpp"

namespace obotcha {

DECLARE_CLASS(Executor) {
public:
    enum Status {
        Executing = 0,
        ShutDown,
    };

    enum Priority {
        Low = 0,
        Medium,
        High,
        NoUse
    };

};

}
#endif