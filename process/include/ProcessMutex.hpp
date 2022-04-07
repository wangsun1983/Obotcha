#ifndef __OBOTCHA_PROCESS_MUTEX_HPP__
#define __OBOTCHA_PROCESS_MUTEX_HPP__

#include <thread>
#include <mutex>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ByteArray.hpp"
#include "String.hpp"
#include "HashMap.hpp"
#include "Mutex.hpp"
#include "Lock.hpp"

namespace obotcha {

DECLARE_CLASS(ProcessMutex) IMPLEMENTS(Lock){
public:
    _ProcessMutex(String);
    int lock();
    int unlock();
    ~_ProcessMutex();

private:
    String mPath;
    int mFd;
};

}
#endif
