#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>

#include "ProcessSem.hpp"
#include "System.hpp"
#include "InitializeException.hpp"

namespace obotcha {

long _ProcessSem::kSemMax = -1;

_ProcessSem::_ProcessSem(String name,int n):mName(name),mNum(n) {
    if(kSemMax == -1) {
        kSemMax = sysconf(_SC_SEM_VALUE_MAX);
    }

    Panic(mNum > kSemMax,InitializeException,"sem num over size")

    mSem = sem_open(mName->toChars(),O_RDWR|O_CREAT, S_IWUSR|S_IRUSR,mNum);
    Panic(mSem == SEM_FAILED,InitializeException,"sem open failed")
}

int _ProcessSem::wait() {
    return sem_wait(mSem);
}

/**
 * wait if count is zero
 * */
int _ProcessSem::wait(long timeInterval) {
    if(timeInterval == 0) {
        return wait();
    }
    
    struct timespec ts;
    st(System)::GetNextTime(timeInterval,&ts);
    return sem_timedwait(mSem, &ts);
}

int _ProcessSem::tryWait() {
    return sem_trywait(mSem);
}

/**
 * Process A:post()
 * after 1 second
 * Process B:wait() 
 * ->it cost no time,because Thread A's post will increase count.
 * it looks like freertos's lock~~.
 * */
int _ProcessSem::post() {
    return sem_post(mSem);
}

int _ProcessSem::getValue() {
    int value;
    sem_getvalue(mSem,&value);
    return value;

}

void _ProcessSem::clear() {
    close();
    sem_unlink(mName->toChars());
}

void _ProcessSem::close() {
    if(mSem != nullptr) {
        sem_close(mSem);
        mSem = nullptr;
    }
}

_ProcessSem::~_ProcessSem() {
    sem_close(mSem);
}

}

