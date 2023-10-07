#ifndef __OBOTCHA_PROCESS_MUTEX_HPP__
#define __OBOTCHA_PROCESS_MUTEX_HPP__

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

#include "Object.hpp"
#include "String.hpp"
#include "Lock.hpp"
#include "ShareMemory.hpp"
#include "Concurrent.hpp"
#include "Mutex.hpp"

namespace obotcha {

DECLARE_CLASS(ProcessMutex) IMPLEMENTS(Lock){
public:
    friend class _ProcessCondition;
    
    explicit _ProcessMutex(String id);
    int lock(long interval = st(Concurrent)::kWaitForEver) override;
    int unlock() override;
    int tryLock();
    
    ~_ProcessMutex() override;

    static void Clear(String id);
    static void Create(String id,st(Lock)::Type type = st(Lock)::Type::Recursive);

private:
    pthread_mutex_t *getMutex_t();

    String mId;
    pthread_mutex_t *mMutex = nullptr;
    int mMutexFd = -1;
};

}
#endif
