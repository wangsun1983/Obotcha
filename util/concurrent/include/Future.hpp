#ifndef __FUTURE_HPP__
#define __FUTURE_HPP__

#include "FutureTask.hpp"

namespace obotcha {

enum FutureStatus {
    FUTURE_WAITING,
    FUTURE_RUNNING,
    FUTURE_COMPLETE
};

DECLARE_SIMPLE_CLASS(Future) {
public:
    _Future(FutureTask);

    void wait();
    
    void wait(long);
    
    void cancel();
    
private:
    FutureTask mTask;    
};

}
#endif