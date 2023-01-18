#include <fcntl.h>
#include <semaphore.h>

#include "ProcessSem.hpp"
#include "System.hpp"
#include "InitializeException.hpp"

namespace obotcha {

long _ProcessSem::SEM_MAX_VALUE = -1;

_ProcessSem::_ProcessSem(String name,int n) {
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

int _ProcessSem::wait() {
    return sem_wait(sem);
}

/**
 * wait if count is zero
 * */
int _ProcessSem::wait(long timeInterval) {
    if(timeInterval == 0) {
        return wait();
    }
    
    struct timespec ts;
    st(System)::getNextTime(timeInterval,&ts);
    return sem_timedwait(sem, &ts);
}

int _ProcessSem::tryWait() {
    return sem_trywait(sem);
}

/**
 * Process A:post()
 * after 1 second
 * Process B:wait() 
 * ->it cost no time,because Thread A's post will increase count.
 * it looks like freertos's lock~~.
 * */
int _ProcessSem::post() {
    return sem_post(sem);
}

int _ProcessSem::getValue() {
    int value;
    sem_getvalue(sem,&value);
    return value;

}

void _ProcessSem::clear() {
    close();
    sem_unlink(mName->toChars());
}

void _ProcessSem::close() {
    if(sem != nullptr) {
        sem_close(sem);
        sem = nullptr;
    }
}

_ProcessSem::~_ProcessSem() {
    sem_close(sem);
}

}

