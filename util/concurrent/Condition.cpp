/**
 * @file Condition.cpp
 * @brief Causes the current thread to wait until it is signalled
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include "AutoLock.hpp"
#include "Condition.hpp"
#include "InitializeException.hpp"
#include "Mutex.hpp"
#include "System.hpp"
#include "Log.hpp"
#include "TimeWatcher.hpp"
#include "PermissionException.hpp"

namespace obotcha {

_Condition::_Condition() {
    if (pthread_cond_init(&cond_t, nullptr) != 0) {
        Trigger(InitializeException, "Condition error")
    }
    count = 0;
}

_Condition::_Condition(String name) {
    this->mName = name;
    if (pthread_cond_init(&cond_t, nullptr) != 0) {
        Trigger(InitializeException, "Condition error")
    }
    count = 0;
}

/**
 * @brief Wait on the condition variable.
 * 
 * This function makes the current thread wait on the condition variable, 
 * releasing the associated mutex before waiting and reacquiring it after.
 * It's used in multi-threading to manage synchronization between threads.
 * 
 * @param m The mutex associated with the condition variable, which must be locked by the current thread before calling this function.
 * @param interval The maximum time(ms) to wait, in milliseconds. If it's st(Concurrent)::kWaitForEver(0L), it will wait indefinitely.
 * @return int Returns 0 on success, or an error code(Negative) on failure.
 * 
 * Note:
 * - It first checks if the current thread holds the lock for the mutex.
 * - It then increases the wait count to track the number of threads waiting on this condition variable.
 * - Depending on whether a timeout interval is specified, it calls pthread_cond_wait or pthread_cond_timedwait to wait on the condition variable.
 * - After waiting, it decreases the wait count and returns the result of the wait operation.
 */
int _Condition::wait(const Mutex &m, long interval) {
    //check mutex owner
    Panic(!m->isOwner(),PermissionException,"wait without mutex lock")

    int ret = 0;
    pthread_mutex_t *mutex_t = m->getMutex_t();

    count++;
    if (interval == st(Concurrent)::kWaitForEver) {
        ret = -pthread_cond_wait(&cond_t, mutex_t);
    } else {
        struct timespec ts = {0};
        st(System)::GetNextTime(interval, &ts);
        ret = -pthread_cond_timedwait(&cond_t, mutex_t, &ts);
    }
    count--;
    return ret;
}

int _Condition::wait(const AutoLock &m, long interval) {
    if(IsInstance(Mutex,m.mLock)) {
        Mutex mu = Cast<Mutex>(m.mLock);
        return wait(mu,interval);
    }
    return -1;
}

int _Condition::wait(const sp<_Mutex> &m,const std::function<bool()>& predFunc)  {
    int ret = 0;
    while(!predFunc() && (ret = wait(m)) == 0) {
    }
    return ret;
}

int _Condition::wait(const AutoLock &m,const std::function<bool()>& predFunc) {
    if(IsInstance(Mutex,m.mLock)) {
        Mutex mu = Cast<Mutex>(m.mLock);
        return wait(mu,predFunc);
    }
    return -1;
}

int _Condition::wait(const Mutex &m,long millseconds,const std::function<bool()>& predFunc) {
    if(!m->isOwner()) {
        Trigger(PermissionException,"wait without mutex lock")
    }

    TimeWatcher watch = TimeWatcher::New();
    bool isWaitForEver = (millseconds == st(Concurrent)::kWaitForEver);
    while(!predFunc()) {
        if(!isWaitForEver) {
            watch->start();
        }
        if(wait(m,millseconds) != 0) {
            return -ETIMEDOUT;
        }
        if(!isWaitForEver) {
            millseconds -= watch->stop();
            if(millseconds < 0) {
                return -ETIMEDOUT;
            }
        }
    }

    return 0;
}

int _Condition::wait(const AutoLock &m,long millseconds,const std::function<bool()>& predFunc) {
    if(IsInstance(Mutex,m.mLock)) {
        Mutex mu = Cast<Mutex>(m.mLock);
        return wait(mu,millseconds,predFunc);
    }
    Trigger(PermissionException,"need Mutex")
}

void _Condition::notify() {
    pthread_cond_signal(&cond_t);
}

void _Condition::notifyAll() {
    pthread_cond_broadcast(&cond_t);
}

_Condition::~_Condition() {
    pthread_cond_destroy(&cond_t);
}

int _Condition::getWaitCount() {
    return count;
}

} // namespace obotcha
