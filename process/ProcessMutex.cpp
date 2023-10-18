#include <unistd.h>

#include "ProcessMutex.hpp"
#include "InitializeException.hpp"
#include "File.hpp"
#include "System.hpp"
#include "IO.hpp"
#include "AutoLock.hpp"

namespace obotcha {

_ProcessMutex::_ProcessMutex(String name):mName(name) {
    mMutexFd = shm_open(mName->toChars(), O_RDWR , S_IRWXU|S_IRWXG);
    if(mMutexFd < 0) {
        Trigger(InitializeException,"fail to acquire share memory")
    }

    mMutex = (pthread_mutex_t *) mmap(nullptr, 
                                    sizeof(pthread_mutex_t), 
                                    PROT_READ | PROT_WRITE, 
                                    MAP_SHARED, mMutexFd, 0);
    if (mMutex == MAP_FAILED) {
        Trigger(InitializeException,"fail to map share memory")
    }
}

int _ProcessMutex::lock(long interval) {
    if (interval == st(Concurrent)::kWaitForEver) {
        return -pthread_mutex_lock(mMutex);
    } else {
        struct timespec ts = {0};
        st(System)::GetNextTime(interval, &ts);
        return -pthread_mutex_timedlock(mMutex, &ts);
    }
}

int _ProcessMutex::unlock() {
    return -pthread_mutex_unlock(mMutex);
}

int _ProcessMutex::tryLock() {
    return -pthread_mutex_trylock(mMutex);
}

void _ProcessMutex::Clear(String name) {
    auto fd = shm_open(name->toChars(),O_RDWR , 0666);
    if(fd < 0) {
        return;
    }

    shm_unlink(name->toChars());
    close(fd);
}

void _ProcessMutex::Create(String name,st(Lock)::Type type) {
    Clear(name);
    auto fd = shm_open(name->toChars(), O_CREAT|O_RDWR , S_IRWXU|S_IRWXG);
    auto mutex = (pthread_mutex_t *) mmap(nullptr, 
                                    sizeof(pthread_mutex_t), 
                                    PROT_READ | PROT_WRITE, 
                                    MAP_SHARED, fd, 0);
    ftruncate(fd, sizeof(pthread_mutex_t));
    
    pthread_mutexattr_t mattr;
    pthread_mutexattr_init(&mattr);
    if(type == st(Lock)::Type::Recursive) {
        pthread_mutexattr_settype(&mattr, PTHREAD_MUTEX_RECURSIVE);
    }
    pthread_mutexattr_setpshared(&mattr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(mutex, &mattr);
    pthread_mutexattr_destroy(&mattr);

    munmap(mutex,sizeof(pthread_mutex_t));
    close(fd);
}

pthread_mutex_t *_ProcessMutex::getMutex_t() {
    return mMutex;
}

_ProcessMutex::~_ProcessMutex() {
    if(mMutex != nullptr) {
        munmap(mMutex,sizeof(pthread_mutex_t));
        mMutex = nullptr;
    }

    if(mMutexFd != -1) {
        close(mMutexFd);
        mMutexFd = -1;
    }
}

}
