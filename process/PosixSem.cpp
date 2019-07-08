#include <errno.h>
#include <string.h>
#include <unistd.h>  

#include "PosixSem.hpp"
#include "System.hpp"

namespace obotcha {

long _PosixSem::SEM_MAX_VALUE = -1;

_PosixSem::_PosixSem(String name,int n) {
    mName = name;
    num = n;
    sem = SEM_FAILED;
    if(SEM_MAX_VALUE == -1) {
        SEM_MAX_VALUE = sysconf(_SC_SEM_VALUE_MAX);
    }
}

bool _PosixSem::init() {
    //printf("Posix sem init num is %d \n",num);

    if(num > SEM_MAX_VALUE) {
        return false;
    }

    sem = sem_open(mName->toChars(),O_RDWR|O_CREAT, S_IWUSR|S_IRUSR,num);
    return (sem != SEM_FAILED);
}

int _PosixSem::wait() {
    if(sem == SEM_FAILED) {
        return -PosixSemNotCreat;
    }

    return sem_wait(sem);
}

int _PosixSem::wait(long timeInterval) {
    if(sem == SEM_FAILED) {
        return -PosixSemNotCreat;
    }

    struct timespec ts;
    /*
    clock_gettime(CLOCK_REALTIME, &ts);
    long secs = timeInterval/1000;
    timeInterval = timeInterval%1000;
    
    long add = 0;
    timeInterval = timeInterval*1000*1000 + ts.tv_nsec;
    add = timeInterval / (1000*1000*1000);
    ts.tv_sec += (add + secs);
    ts.tv_nsec = timeInterval%(1000*1000*1000);
    */
    st(System)::getNextTime(timeInterval,&ts);
    return sem_timedwait(sem, &ts);
}

int _PosixSem::tryWait() {
    if(sem == SEM_FAILED) {
        return -PosixSemNotCreat;
    }

    return sem_trywait(sem);
}

int _PosixSem::post() {
    if(sem == SEM_FAILED) {
        return -PosixSemNotCreat;
    }

    return sem_post(sem);
}

int _PosixSem::getValue() {
    if(sem == SEM_FAILED) {
        return -PosixSemNotCreat;
    }

    int value;
    sem_getvalue(sem,&value);
    return value;

}

void _PosixSem::destroy() {
    sem_close(sem);
    sem_unlink(mName->toChars());
}

void _PosixSem::release() {
    sem_close(sem);
}


void _PosixSem::clean() {
    sem_close(sem);
    sem_unlink(mName->toChars());
}

_PosixSem::~_PosixSem() {
    sem_close(sem);
}

}

