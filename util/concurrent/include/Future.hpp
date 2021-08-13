#ifndef __OBOTCHA_FUTURE_HPP__
#define __OBOTCHA_FUTURE_HPP__

#include "ExecutorTask.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Future) {
public:
    _Future(ExecutorTask);
    
    ~_Future();
    
    void wait(long interval = 0);
    
    int cancel();

    template<typename T>
    T getResult(long millseconds = 0) {
        return mTask->getResult<T>(millseconds);
    }
    
    enum Status {
        Waiting = st(ExecutorTask)::Waiting,
        Running,
        Cancel,
        Complete,
    };

private:
    ExecutorTask mTask;
};

}
#endif