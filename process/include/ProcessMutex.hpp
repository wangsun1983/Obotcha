#ifndef __OBOTCHA_PROCESS_MUTEX_HPP__
#define __OBOTCHA_PROCESS_MUTEX_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "Lock.hpp"
#include "FileDescriptor.hpp"

namespace obotcha {

DECLARE_CLASS(ProcessMutex) IMPLEMENTS(Lock){
public:
    _ProcessMutex(String);
    int lock(long interval = 0);
    int unlock();
    ~_ProcessMutex();

private:
    String mPath;
    FileDescriptor mFd;
};

}
#endif
