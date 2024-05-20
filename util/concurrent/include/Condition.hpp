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
#include <atomic>

#include "Object.hpp"
#include "AutoLock.hpp"
#include "Mutex.hpp"
#include "OStdInstanceOf.hpp"
#include "Concurrent.hpp"

namespace obotcha {

DECLARE_CLASS(Condition) {
public:
    _Condition();

    _Condition(String);

    ~_Condition() override;

    int wait(const Mutex &m, long interval = st(Concurrent)::kWaitForEver);
    int wait(const AutoLock &m, long interval = st(Concurrent)::kWaitForEver);
    
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

    int wait(const Mutex &m,const std::function<bool()> & predFunc);
    int wait(const AutoLock & m,const std::function<bool()> & predFunc);

    int wait(const Mutex &m,long interval,const std::function<bool()>& predFunc);
    int wait(const AutoLock &m,long interval,const std::function<bool()>& predFunc);

    void notify();
    void notifyAll();
    int getWaitCount();

private:
    pthread_cond_t cond_t;
    std::atomic_int count;
    String mName;
};

} // namespace obotcha
#endif