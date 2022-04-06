#include <errno.h>
#include <string.h>
#include <unistd.h>  

#include "PosixSem.hpp"
#include "System.hpp"
#include "Error.hpp"

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
    if(num > SEM_MAX_VALUE) {
        return false;
    }

    sem = sem_open(mName->toChars(),O_RDWR|O_CREAT, S_IWUSR|S_IRUSR,num);
    return (sem != SEM_FAILED);
}

int _PosixSem::wait() {
    if(sem == SEM_FAILED) {
        return -1;
    }

    return sem_wait(sem);
}

int _PosixSem::wait(long timeInterval) {
    if(sem == SEM_FAILED) {
        return -1;
    }

    struct timespec ts;
    st(System)::getNextTime(timeInterval,&ts);
    return sem_timedwait(sem, &ts);
}

int _PosixSem::tryWait() {
    if(sem == SEM_FAILED) {
        return -1;
    }

    return sem_trywait(sem);
}

int _PosixSem::post() {
    if(sem == SEM_FAILED) {
        return -1;
    }

    return sem_post(sem);
}

int _PosixSem::getValue() {
    if(sem == SEM_FAILED) {
        return -1;
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

