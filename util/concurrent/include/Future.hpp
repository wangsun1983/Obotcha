#ifndef __OBOTCHA_FUTURE_HPP__
#define __OBOTCHA_FUTURE_HPP__

#include "ExecutorTask.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Future) {
public:
    _Future(ExecutorTask);
    
    ~_Future();

    void wait();
    
    void wait(long);
    
    int cancel();

    template<typename T>
    T getResult(T defaultvalue,long millseconds = 0) {
        return mTask->getResult<T>(defaultvalue,millseconds);
    }
    
    enum Status {
        Waiting = 0,
        Running,
        Cancel,
        Complete,
    };

private:
    ExecutorTask mTask;
};

}
#endif