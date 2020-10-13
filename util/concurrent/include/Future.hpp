#ifndef __OBOTCHA_FUTURE_HPP__
#define __OBOTCHA_FUTURE_HPP__

#include "FutureTask.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Future) {
public:
    _Future(FutureTask);
    
    ~_Future();

    void wait();
    
    void wait(long);
    
    int cancel();

    template<typename T>
    T getResult() {
        return mTask->getResult<T>();
    }

    static const int Waiting = 0;
    static const int Running = 1;
    static const int Cancel = 2;
    static const int Complete = 3;
    static const int Error = 4;

private:
    FutureTask mTask;
};

}
#endif