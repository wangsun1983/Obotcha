#include <errno.h>
#include <string.h>
#include <unistd.h>  

#include "PosixSem.hpp"
#include "System.hpp"
#include "Error.hpp"
#include "InitializeException.hpp"

namespace obotcha {

long _PosixSem::SEM_MAX_VALUE = -1;

_PosixSem::_PosixSem(String name,int n) {
    mName = name;
    num = n;
    if(SEM_MAX_VALUE == -1) {
        SEM_MAX_VALUE = sysconf(_SC_SEM_VALUE_MAX);
    }

    sem = sem_open(mName->toChars(),O_RDWR|O_CREAT, S_IWUSR|S_IRUSR,num);
    if(sem == SEM_FAILED) {
        Trigger(InitializeException,"sem open failed");
    }
}

int _PosixSem::wait() {
    return sem_wait(sem);
}

/**
 * wait if count is zero
 * */
int _PosixSem::wait(long timeInterval) {
    if(timeInterval == 0) {
        return wait();
    }
    
    struct timespec ts;
    st(System)::getNextTime(timeInterval,&ts);
    return sem_timedwait(sem, &ts);
}

int _PosixSem::tryWait() {
    return sem_trywait(sem);
}

/**
 * Process A:post()
 * after 1 second
 * Process B:wait() 
 * ->it cost no time,because Thread A's post will increase count.
 * it looks like freertos's lock~~.
 * */
int _PosixSem::post() {
    return sem_post(sem);
}

int _PosixSem::getValue() {
    int value;
    sem_getvalue(sem,&value);
    return value;

}

void _PosixSem::clear() {
    close();
    sem_unlink(mName->toChars());
}

void _PosixSem::close() {
    if(sem != nullptr) {
        sem_close(sem);
        sem = nullptr;
    }
}

_PosixSem::~_PosixSem() {
    sem_close(sem);
}

}

