#include "PosixAnonymousSem.hpp"

namespace obotcha {

_PosixAnonymousSem::_PosixAnonymousSem(int n) {
    num = n;
}

bool _PosixAnonymousSem::init() {
    int res = sem_init(&sem,0,0);
    return (res == 0);
}

void _PosixAnonymousSem::tryWait() {
    sem_trywait(&sem);
}

void _PosixAnonymousSem::wait() {
    sem_wait(&sem);
}

void _PosixAnonymousSem::wait(long timeInterval) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    long secs = timeInterval/1000;
    timeInterval = timeInterval%1000;
    
    long add = 0;
    timeInterval = timeInterval*1000*1000 + ts.tv_nsec;
    add = timeInterval / (1000*1000*1000);
    ts.tv_sec += (add + secs);
    ts.tv_nsec = timeInterval%(1000*1000*1000);
    sem_timedwait(&sem, &ts);
}

void _PosixAnonymousSem::post() {
    sem_post(&sem);
}

int _PosixAnonymousSem::getValue() {
    int value;
    sem_getvalue(&sem,&value);
    return value;
}

void _PosixAnonymousSem::destroy() {
    sem_destroy(&sem);
}

_PosixAnonymousSem::~_PosixAnonymousSem() {

}



}
