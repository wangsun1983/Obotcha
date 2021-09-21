#ifndef __OBOTCHA_EXECUTOR_HPP__
#define __OBOTCHA_EXECUTOR_HPP__

#include "Condition.hpp"
#include "InterruptedException.hpp"
#include "Mutex.hpp"
#include "OStdInstanceOf.hpp"
#include "Runnable.hpp"
#include "TimeOutException.hpp"

namespace obotcha {

DECLARE_CLASS(Executor) {
public:
    enum Status {
        Executing = 0,
        ShutDown,
    };

    enum Priority { Low = 0, Medium, High, NoUse };
};

} // namespace obotcha
#endif