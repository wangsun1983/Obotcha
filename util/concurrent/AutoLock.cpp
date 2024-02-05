/**
 * @file AutoLock.cpp
 * @brief  A simple class that locks a given mutex on construction
 * and unlocks it when it goes out of scope. 
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2024-01-15
 * @license none
 */

#include "AutoLock.hpp"
#include "IllegalStateException.hpp"

namespace obotcha {

AutoLock::AutoLock(Lock lock){
    if(lock != nullptr) {
        lock->lock();
        mLock = lock;
    }
}

AutoLock::~AutoLock() {
    if(mLock != nullptr) {
        try {
            mLock->unlock();
        } catch(IllegalStateException &) {
            //use try/catch for this case:
            //Synchronize(mMutex) 
            //for(AutoLock __l__(X);X->isOwner();__l__.release())
            //__l__ has release the look,so lock owner is 0
            //when AutoLock destruct itself,mutex's unlock will be called
            //again.but the owner is already set as 0 when __l__.release()
            //so it will crash.
        }
    }
}

void AutoLock::release() {
    if(mLock != nullptr) {
        mLock->unlock();
    }
}

}
