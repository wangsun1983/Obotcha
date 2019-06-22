#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

#include "Condition.hpp"
#include "Object.hpp"

namespace obotcha {

_Condition::_Condition():cond_t(PTHREAD_COND_INITIALIZER) {
    //TODO nothing
}

void _Condition::wait(Mutex m) {
    pthread_mutex_t* mutex_t = m->getMutex_t();
    pthread_cond_wait(&cond_t,mutex_t);
}

int _Condition::wait(Mutex m,long int timeInterval) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    long secs = timeInterval/1000;
    timeInterval = timeInterval%1000;

    long add = 0;
    timeInterval = timeInterval*1000*1000 + ts.tv_nsec;
    add = timeInterval / (1000*1000*1000);
    ts.tv_sec += (add + secs);
    ts.tv_nsec = timeInterval%(1000*1000*1000);

    pthread_mutex_t* mutex_t = m->getMutex_t();

    int ret = pthread_cond_timedwait(&cond_t,mutex_t,&ts);
    if(ret == ETIMEDOUT) {
        return NotifyByTimeout;
    }

    return NotifyByThread;
}

void _Condition::notify() {
    //cond.notify_one();
    pthread_cond_signal(&cond_t);
}

void _Condition::notifyAll() {
    //cond.notify_all();
    pthread_cond_broadcast(&cond_t);
}

}