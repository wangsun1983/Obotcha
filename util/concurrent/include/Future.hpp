#ifndef __FUTURE_HPP__
#define __FUTURE_HPP__

#include "FutureTask.hpp"

namespace obotcha {

enum FutureStatus {
    FUTURE_WAITING,
    FUTURE_RUNNING,
    FUTURE_CANCEL,
    FUTURE_COMPLETE
};

DECLARE_SIMPLE_CLASS(Future) {
public:
    _Future(FutureTask);
    
    ~_Future();

    void wait();
    
    void wait(long);
    
    int cancel();
    
private:
    FutureTask mTask;    
};

}
#endif