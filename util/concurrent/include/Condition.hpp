/**
 * @file Condition.hpp
 * @brief  Condition provide a means for one thread to
 *         suspend execution until notified by another
 *         thread that some state condition may now be true. 
 *         Because access to this shared state information occurs in 
 *         different threads, it must be protected, so a lock of 
 *         some form is associated with the condition. The key property 
 *         that waiting for a condition provides is that it atomically
 *         releases the associated lock and suspends the current thread, 
 *         just like wait.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.2
 * @date 2022-10-19
 * @license none
 * @history
 * 1.2022-10-19: Add lambda function for await
 */

#ifndef __OBOTCHA_CONDITION_HPP__
#define __OBOTCHA_CONDITION_HPP__

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