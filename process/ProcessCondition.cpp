#include <unistd.h>

#include "ProcessCondition.hpp"
#include "InitializeException.hpp"
#include "System.hpp"
#include "OStdInstanceOf.hpp"
#include "PermissionException.hpp"

namespace obotcha {

_ProcessCondition::_ProcessCondition(String name):mName(name) {
    mConditionFd = shm_open(mName->toChars(), O_RDWR , S_IRWXU|S_IRWXG);
    if(mConditionFd < 0) {
        Trigger(InitializeException,"fail to acquire share memory")
    }
    mCond = (pthread_cond_t *) mmap(nullptr, 
                                    sizeof(pthread_cond_t), 
                                    PROT_READ | PROT_WRITE, 
                                    MAP_SHARED, mConditionFd, 0);
    if (mCond == MAP_FAILED) {
        Trigger(InitializeException,"fail to map share memory")
    }
}

int _ProcessCondition::wait(ProcessMutex m, long int interval) {
    int ret = 0;
    pthread_mutex_t *mutex_t = m->getMutex_t();
    if (interval == st(Concurrent)::kWaitForEver) {
        ret = -pthread_cond_wait(mCond, mutex_t);
    } else {
        struct timespec ts = {0};
        st(System)::GetNextTime(interval, &ts);
        ret = -pthread_cond_timedwait(mCond, mutex_t, &ts);
    }
    return ret;
}

int _ProcessCondition::wait(AutoLock &m, long int millseconds) {
    if(IsInstance(ProcessMutex,m.mLock)) {
        ProcessMutex mu = Cast<ProcessMutex>(m.mLock);
        return wait(mu,millseconds);
    }
    Trigger(PermissionException,"need Mutex")
}

void _ProcessCondition::notify() {
    pthread_cond_signal(mCond);
}

void _ProcessCondition::notifyAll() {
    pthread_cond_broadcast(mCond);
}

void _ProcessCondition::Clear(String name) {
    auto fd = shm_open(name->toChars(),O_RDWR , 0666);
    if(fd < 0) {
        return;
    }

    shm_unlink(name->toChars());
    close(fd);
}

void _ProcessCondition::Create(String name) {
    Clear(name);
    auto fd = shm_open(name->toChars(), O_CREAT|O_RDWR , S_IRWXU|S_IRWXG);
    auto cond = (pthread_cond_t *) mmap(nullptr, 
                                    sizeof(pthread_cond_t), 
                                    PROT_READ | PROT_WRITE, 
                                    MAP_SHARED, fd, 0);
    ftruncate(fd, sizeof(pthread_cond_t));
    
    pthread_condattr_t  mattr;
    pthread_condattr_init(&mattr);
    pthread_condattr_setpshared(&mattr, PTHREAD_PROCESS_SHARED);
    pthread_cond_init(cond, &mattr);
    pthread_condattr_destroy(&mattr);

    munmap(cond,sizeof(pthread_cond_t));
    close(fd);
}

_ProcessCondition::~_ProcessCondition() {
    if(mCond != nullptr) {
        munmap(mCond,sizeof(pthread_cond_t));
        mCond = nullptr;
    }

    if(mConditionFd != -1) {
        close(mConditionFd);
        mConditionFd = -1;
    }
}

}
