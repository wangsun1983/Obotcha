#ifndef __OBOTCHA_CONCURRENT_HPP__
#define __OBOTCHA_CONCURRENT_HPP__

#include "Object.hpp"

namespace obotcha {

DECLARE_CLASS(Concurrent) {
public:
    enum class Status {
        NotStart = 1,
        Idle,
        WaitingStart, // for lambda
        Running,
        Interrupt, //for thread & task
        Complete, //end of thread
        ShutDown, //end of executor
        Error,
    };

    enum class TaskPriority { 
        Low = 0, 
        Medium, 
        High,
    };
};

} // namespace obotcha
#endif
