#ifndef __OBOTCHA_CONDITION_HPP__
#define __OBOTCHA_CONDITION_HPP__

#include <atomic>
#include <pthread.h>
#include <functional>

#include "Object.hpp"
#include "AutoLock.hpp"

namespace obotcha {

class _Mutex;

DECLARE_CLASS(Condition) {
public:
    _Condition();

    ~_Condition();

    int wait(sp<_Mutex> &m, long int interval = 0);
    int wait(AutoLock &m, long int interval = 0);
    
    //interface sample:
    //external/llvm-project/libcxx/include/condition_variable
    //template <class _Lock, class _Predicate>
    //inline
    //void
    //condition_variable_any::wait(_Lock& __lock, _Predicate __pred)
    //{
    //     while (!__pred())
    //         wait(__lock);
    // }
    int wait(sp<_Mutex> &m,std::function<bool()> predFunc);
    int wait(AutoLock & m,std::function<bool()> predFunc);

    int wait(sp<_Mutex> &m,long int interval,std::function<bool()> predFunc);
    int wait(AutoLock &m,long int interval,std::function<bool()> predFunc);

    void notify();

    void notifyAll();

private:
    pthread_cond_t cond_t;
};

} // namespace obotcha
#endif