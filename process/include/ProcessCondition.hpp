#ifndef __OBOTCHA_PROCESS_CONDITION_HPP__
#define __OBOTCHA_PROCESS_CONDITION_HPP__

#include <thread>
#include <mutex>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ByteArray.hpp"
#include "String.hpp"
#include "HashMap.hpp"
#include "Mutex.hpp"
#include "Lock.hpp"
#include "ProcessMutex.hpp"
#include "AutoLock.hpp"
#include "PosixSem.hpp"
#include "PosixShareMemory.hpp"
#include "ByteArrayReader.hpp"
#include "ByteArrayWriter.hpp"

namespace obotcha {

DECLARE_CLASS(ProcessCondition) {
public:
    _ProcessCondition(String path);
    int wait(ProcessMutex m, long int millseconds = 0);
    int wait(AutoLock &m, long int millseconds = 0);
    void notify();
    void notifyAll();

private:
    void increase(int);
    String mPath;
    int mFd;

    PosixSem sem;
    ProcessMutex mMutex;
    PosixShareMemory mCount;
};

}
#endif
