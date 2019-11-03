#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

#include "Condition.hpp"
#include "Object.hpp"
#include "System.hpp"

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
    if(timeInterval == 0) {
        wait(m);
    } else {
        st(System)::getNextTime(timeInterval,&ts);
        pthread_mutex_t* mutex_t = m->getMutex_t();
        int ret = pthread_cond_timedwait(&cond_t,mutex_t,&ts);

        printf("condition wait ret is %d \n",ret);
        if(ret == ETIMEDOUT) {
            return NotifyByTimeout;
        }
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