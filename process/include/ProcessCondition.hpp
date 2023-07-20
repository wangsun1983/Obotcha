#ifndef __OBOTCHA_PROCESS_CONDITION_HPP__
#define __OBOTCHA_PROCESS_CONDITION_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "Mutex.hpp"
#include "ProcessMutex.hpp"
#include "AutoLock.hpp"
#include "ProcessSem.hpp"
#include "ShareMemory.hpp"

namespace obotcha {

DECLARE_CLASS(ProcessCondition) {
public:
    explicit _ProcessCondition(String path);
    int wait(ProcessMutex m, long int millseconds = 0);
    int wait(AutoLock &m, long int millseconds = 0);
    void notify();
    void notifyAll();
    ~_ProcessCondition();

private:
    void increase(int);
    String mPath;
    int mFd;

    ProcessSem mSem;
    ProcessMutex mMutex;
    ShareMemory mCount;
};

}
#endif
