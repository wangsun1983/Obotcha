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
#include "OStdInstanceOf.hpp"
#include "TimeWatcher.hpp"
#include "PermissionException.hpp"

namespace obotcha {

_Condition::_Condition() {
    if (pthread_cond_init(&cond_t, nullptr) != 0) {
        Trigger(InitializeException, "Condition error");
    }
}

int _Condition::wait(Mutex &m, long int interval) {
    pthread_mutex_t *mutex_t = m->getMutex_t();
    //check mutex owner
    if(!m->isOwner()) {
        Trigger(PermissionException,"wait without mutex lock");
    }
    
    //wangsl
    count++;
    //wangsl

    if (interval == 0) {
        int ret = -pthread_cond_wait(&cond_t, m->getMutex_t());
        count--;
        return ret;
    }
    struct timespec ts = {0};
    st(System)::getNextTime(interval, &ts);
    int ret = -pthread_cond_timedwait(&cond_t, mutex_t, &ts);
    count--;
    return ret;
}

int _Condition::wait(AutoLock &m, long int interval) {
    if(IsInstance(Mutex,m.mLock)) {
        Mutex mu = Cast<Mutex>(m.mLock);
        return wait(mu,interval);
    }
    return -1;
}

int _Condition::wait(sp<_Mutex> &m,std::function<bool()> predFunc)  {
    while(!predFunc()) {
        int ret = wait(m);
        if(ret < 0) {
            return ret;
        }
    }
    return 0;
}

int _Condition::wait(AutoLock &m,std::function<bool()> predFunc) {
    if(IsInstance(Mutex,m.mLock)) {
        Mutex mu = Cast<Mutex>(m.mLock);
        return wait(mu,predFunc);
    }
    return -1;
}

int _Condition::wait(sp<_Mutex> &m,long int millseconds,std::function<bool()> predFunc) {
    if(!m->isOwner()) {
        Trigger(PermissionException,"wait without mutex lock");
    }

    TimeWatcher watch = createTimeWatcher();
    bool isWaitForEver = (millseconds == 0);
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

int _Condition::wait(AutoLock &m,long int millseconds,std::function<bool()> predFunc) {
    if(IsInstance(Mutex,m.mLock)) {
        Mutex mu = Cast<Mutex>(m.mLock);
        return wait(mu,millseconds,predFunc);
    }
    return -1;
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
