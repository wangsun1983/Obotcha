#include <stdio.h>
#include <unistd.h>

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

void _Condition::wait(Mutex m,long int millseconds) {
    struct timespec abstime;
    struct timeval now;
    
    gettimeofday(&now, NULL);

    abstime.tv_sec = now.tv_sec + millseconds/1000;
    abstime.tv_nsec = now.tv_usec + (millseconds%1000)*1000;

    pthread_mutex_t* mutex_t = m->getMutex_t();

    pthread_cond_timedwait(&cond_t,mutex_t,&abstime);
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