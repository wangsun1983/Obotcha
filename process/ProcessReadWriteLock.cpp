#include <unistd.h>

#include "ProcessReadWriteLock.hpp"
#include "File.hpp"
#include "IO.hpp"
#include "System.hpp"
#include "InitializeException.hpp"

namespace obotcha {

int _ProcessReadLock::lock(long interval) {
    //return rwlock->mFd->lock(st(IO)::FileLockFlags::ReadLock);
    if (interval == st(Concurrent)::kWaitForEver) {
        return -pthread_rwlock_rdlock(rwlock->mRwlock);
    } else {
        struct timespec ts = {0};
        st(System)::GetNextTime(interval, &ts);
        return -pthread_rwlock_timedrdlock(rwlock->mRwlock, &ts);
    }
}

int _ProcessReadLock::unlock() {
    //return rwlock->mFd->unlock();
    return pthread_rwlock_unlock(rwlock->mRwlock);
}

// String _ProcessReadLock::getPath() {
//     return rwlock->getPath();
// }

_ProcessReadLock::_ProcessReadLock(sp<_ProcessReadWriteLock> lock):rwlock(lock) {
}

//ProcessWriteLock
int _ProcessWriteLock::lock(long interval) {
    //return rwlock->mFd->lock(st(IO)::FileLockFlags::WriteLock);
    if (interval == st(Concurrent)::kWaitForEver) {
        return -pthread_rwlock_wrlock(rwlock->mRwlock);
    } else {
        struct timespec ts = {0};
        st(System)::GetNextTime(interval, &ts);
        return -pthread_rwlock_timedwrlock(rwlock->mRwlock, &ts);
    }
}

int _ProcessWriteLock::unlock() {
    //return rwlock->mFd->unlock();
    return pthread_rwlock_unlock(rwlock->mRwlock);
}

// String _ProcessWriteLock::getPath() {
//     return rwlock->getPath();
// }

_ProcessWriteLock::_ProcessWriteLock(ProcessReadWriteLock r):rwlock(r) {
}

//ProcessReadWriteLock
_ProcessReadWriteLock::_ProcessReadWriteLock(String id) {
    mRwId = id;
    mRwlockFd = shm_open(mRwId->toChars(), O_RDWR , S_IRWXU|S_IRWXG);
    if(mRwlockFd < 0) {
        Trigger(InitializeException,"fail to acquire share memory");
    }

    mRwlock = (pthread_rwlock_t *) mmap(NULL, 
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

// String _ProcessReadWriteLock::getPath() {
//     return mPath;
// }

void _ProcessReadWriteLock::Clear(String id) {
    auto fd = shm_open(id->toChars(),O_RDWR , 0666);
    if(fd < 0) {
        return;
    }

    shm_unlink(id->toChars());
    close(fd);
}

void _ProcessReadWriteLock::Create(String id) {
    Clear(id);
    auto fd = shm_open(id->toChars(), O_CREAT|O_RDWR , S_IRWXU|S_IRWXG);
    auto lock = (pthread_rwlock_t *) mmap(NULL, 
                                    sizeof(pthread_rwlock_t), 
                                    PROT_READ | PROT_WRITE, 
                                    MAP_SHARED, fd, 0);
    ftruncate(fd, sizeof(pthread_rwlock_t));
    munmap(lock,sizeof(pthread_rwlock_t));
    close(fd);
}

_ProcessReadWriteLock::~_ProcessReadWriteLock() {
    // if(mFd != nullptr) {
    //     mFd->close();
    //     mFd = nullptr;
    // }
    //TODO
}

}
