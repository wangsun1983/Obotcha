#include <unistd.h>

#include "ProcessReadWriteLock.hpp"
#include "File.hpp"
#include "IO.hpp"
#include "System.hpp"
#include "InitializeException.hpp"

namespace obotcha {

_ProcessReadLock::_ProcessReadLock(sp<_ProcessReadWriteLock> lock):rwlock(lock) {
}

int _ProcessReadLock::lock(long interval) {
    if (interval == st(Concurrent)::kWaitForEver) {
        return -pthread_rwlock_rdlock(rwlock->mRwlock);
    } else {
        struct timespec ts = {0};
        st(System)::GetNextTime(interval, &ts);
        return -pthread_rwlock_timedrdlock(rwlock->mRwlock, &ts);
    }
}

int _ProcessReadLock::tryLock() {
    return -pthread_rwlock_tryrdlock(rwlock->mRwlock);
}

int _ProcessReadLock::unlock() {
    return -pthread_rwlock_unlock(rwlock->mRwlock);
}

//ProcessWriteLock
_ProcessWriteLock::_ProcessWriteLock(ProcessReadWriteLock r):rwlock(r) {
}

int _ProcessWriteLock::lock(long interval) {
    if (interval == st(Concurrent)::kWaitForEver) {
        return -pthread_rwlock_wrlock(rwlock->mRwlock);
    } else {
        struct timespec ts = {0};
        st(System)::GetNextTime(interval, &ts);
        return -pthread_rwlock_timedwrlock(rwlock->mRwlock, &ts);
    }
}

int _ProcessWriteLock::unlock() {
    return -pthread_rwlock_unlock(rwlock->mRwlock);
}

int _ProcessWriteLock::tryLock() {
    return -pthread_rwlock_trywrlock(rwlock->mRwlock);
}

//ProcessReadWriteLock
_ProcessReadWriteLock::_ProcessReadWriteLock(String name):mName(name) {
    mRwlockFd = shm_open(mName->toChars(), O_RDWR , S_IRWXU|S_IRWXG);
    if(mRwlockFd < 0) {
        Trigger(InitializeException,"fail to acquire share memory")
    }

    mRwlock = (pthread_rwlock_t *) mmap(nullptr, 
                                    sizeof(pthread_rwlock_t), 
                                    PROT_READ | PROT_WRITE, 
                                    MAP_SHARED, mRwlockFd, 0);
    if (mRwlock == MAP_FAILED) {
        Trigger(InitializeException,"fail to map share memory");
    }
}

ProcessReadLock _ProcessReadWriteLock::getReadLock() {
    auto l = new _ProcessReadLock(AutoClone(this));
    return AutoClone(l);
}

ProcessWriteLock _ProcessReadWriteLock::getWriteLock() {
    auto l = new _ProcessWriteLock(AutoClone(this));
    return AutoClone(l);
}

void _ProcessReadWriteLock::Clear(String name) {
    auto fd = shm_open(name->toChars(),O_RDWR , 0666);
    if(fd < 0) {
        return;
    }

    shm_unlink(name->toChars());
    close(fd);
}

void _ProcessReadWriteLock::Create(String name) {
    Clear(name);
    auto fd = shm_open(name->toChars(), O_CREAT|O_RDWR , S_IRWXU|S_IRWXG);
    auto lock = (pthread_rwlock_t *) mmap(nullptr, 
                                    sizeof(pthread_rwlock_t), 
                                    PROT_READ | PROT_WRITE, 
                                    MAP_SHARED, fd, 0);
    ftruncate(fd, sizeof(pthread_rwlock_t));

    pthread_rwlockattr_t  mattr;
    pthread_rwlockattr_init(&mattr);
    pthread_rwlockattr_setpshared(&mattr, PTHREAD_PROCESS_SHARED);
    pthread_rwlock_init(lock, &mattr);
    pthread_rwlockattr_destroy(&mattr);

    munmap(lock,sizeof(pthread_rwlock_t));
    close(fd);
}

_ProcessReadWriteLock::~_ProcessReadWriteLock() {
    if(mRwlock != nullptr) {
        munmap(mRwlock,sizeof(pthread_rwlock_t));
        mRwlock = nullptr;
    }

    if(mRwlockFd != -1) {
        close(mRwlockFd);
        mRwlockFd = -1;
    }
}

}
