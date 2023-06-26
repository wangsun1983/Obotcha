#include "AutoLock.hpp"

namespace obotcha {

AutoLock::AutoLock(Lock lock){
    if(lock != nullptr) {
        lock->lock();
        mLock = lock;
    }
}

AutoLock::~AutoLock() {
    if(mLock != nullptr) {
        mLock->unlock();
    }
}

void AutoLock::release() {
    if(mLock != nullptr) {
        mLock->unlock();
    }
}

}
