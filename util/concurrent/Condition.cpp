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

#include <pthread.h>

#include "AutoLock.hpp"
#include "Condition.hpp"
#include "Error.hpp"
#include "IllegalStateException.hpp"
#include "InitializeException.hpp"
#include "Mutex.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Log.hpp"
#include "OStdInstanceOf.hpp"

namespace obotcha {

_Condition::_Condition() {
    if (pthread_cond_init(&cond_t, nullptr) != 0) {
        Trigger(InitializeException, "Condition error");
    }
}

int _Condition::wait(Mutex m, long int timeInterval) {
    pthread_mutex_t *mutex_t = m->getMutex_t();
    if (timeInterval == 0) {
        if (pthread_cond_wait(&cond_t, m->getMutex_t()) != 0) {
            LOG(ERROR)<<"Condition wait failed";
        }
        return 0;
    }

    struct timespec ts = {0};
    st(System)::getNextTime(timeInterval, &ts);
    int ret = pthread_cond_timedwait(&cond_t, mutex_t, &ts);
    if(ret != 0) {
        LOG(ERROR)<<"Condition wait failed";
        if (ret == ETIMEDOUT) {
            return -WaitTimeout;
        }
        return -1;
    }

    return 0;
}

int _Condition::wait(AutoLock &m, long int millseconds) {
    if(IsInstance(Mutex,m.mLock)) {
        Mutex mu = Cast<Mutex>(m.mLock);
        return wait(mu,millseconds);
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

} // namespace obotcha