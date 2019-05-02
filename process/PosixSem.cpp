#include <errno.h>
#include <string.h>     

#include "PosixSem.hpp"

namespace obotcha {

_PosixSem::_PosixSem(String name,int n) {
    mName = name;
    num = n;
    sem = SEM_FAILED;
}

bool _PosixSem::init() {
    printf("Posix sem init num is %d \n",num);
    sem = sem_open(mName->toChars(),O_RDWR|O_CREAT, S_IWUSR|S_IRUSR,num);
    if(sem == SEM_FAILED) {
        printf("sem_open error is %s \n",strerror(errno));
        return false;
    }

    return true;
}

void _PosixSem::wait() {
    if(sem != SEM_FAILED) {
        sem_wait(sem);
    }
}

void _PosixSem::wait(long timeInterval) {
    if(sem != SEM_FAILED) {
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        long secs = timeInterval/1000;
        timeInterval = timeInterval%1000;
    
        long add = 0;
        timeInterval = timeInterval*1000*1000 + ts.tv_nsec;
        add = timeInterval / (1000*1000*1000);
        ts.tv_sec += (add + secs);
        ts.tv_nsec = timeInterval%(1000*1000*1000);
        sem_timedwait(sem, &ts);
    }   
}

void _PosixSem::tryWait() {
    if(sem != SEM_FAILED) {
        sem_trywait(sem);
    }   
}

void _PosixSem::post() {
    if(sem != SEM_FAILED) {
        sem_post(sem);
    }
}

int _PosixSem::getValue() {
    if(sem != SEM_FAILED) {
        int value;
        sem_getvalue(sem,&value);
        return value;
    }

    return -1;
}

void _PosixSem::destroy() {
    sem_close(sem);
    sem_unlink(mName->toChars());
}

_PosixSem::~_PosixSem() {

}

}

