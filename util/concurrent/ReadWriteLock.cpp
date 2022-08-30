/**
 * @file ReadWriteLock.cpp
 * @brief  ReadWriteLock is a tool for read/write access to a shared resource by
 * multiple threads
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include <pthread.h>

#include "Error.hpp"
#include "ReadWriteLock.hpp"
#include "StrongPointer.hpp"
#include "System.hpp"
#include "Log.hpp"

namespace obotcha {

//------------ ReadLock ------------
_ReadLock::_ReadLock(sp<_ReadWriteLock> l, String s) {
    this->rwlock = l;
    mName = s;
}

int _ReadLock::lock() {
    return rwlock->_readlock();
}

int _ReadLock::unlock() {
    return rwlock->_unReadlock();
}

int _ReadLock::tryLock() {
    return rwlock->_tryReadLock();
}

String _ReadLock::getName() { 
    return mName; 
}

int _ReadLock::lock(long timeInterval) {
    return rwlock->_readlock(timeInterval);
}

//------------ WriteLock ------------//
_WriteLock::_WriteLock(sp<_ReadWriteLock> l, String s) {
    rwlock = l;
    mName = s;
}

int _WriteLock::lock() {
    return rwlock->_writelock();
}

int _WriteLock::unlock() {
    return rwlock->_unWritelock();
}

int _WriteLock::tryLock() {
    return rwlock->_tryWriteLock();
}

String _WriteLock::getName() { 
    return mName;
}

int _WriteLock::lock(long timeInterval) {
    return rwlock->_writelock(timeInterval);
}

//------------ ReadWriteLock ------------
_ReadWriteLock::_ReadWriteLock() : _ReadWriteLock(nullptr) {}

_ReadWriteLock::_ReadWriteLock(String s) {
    mWriteCount = 0;
    mIsWrite = false;

    mMutex = createMutex();
    mReadCondition = createCondition();
    mWriteCondition = createCondition();

    mName = s;
}

sp<_ReadLock> _ReadWriteLock::getReadLock() {
    _ReadLock *l = new _ReadLock(AutoClone(this), mName);
    return AutoClone(l);
}

sp<_WriteLock> _ReadWriteLock::getWriteLock() {
    _WriteLock *l = new _WriteLock(AutoClone(this), mName);
    return AutoClone(l);
}

String _ReadWriteLock::getName() { 
    return mName; 
}

_ReadWriteLock::~_ReadWriteLock() { 
    
}

int _ReadWriteLock::_readlock(long interval) {
    AutoLock l(mMutex);
    int mytid = st(System)::myTid();

    while(mWriteCount != 0 && mytid != mWrOwner) {
        int ret = mReadCondition->wait(mMutex,interval);
        if(ret != 0) {
            return ret;
        }
    }

    printf("readlock trace1,mytid is %d \n",mytid);
    auto iterator = readOwners.find(mytid);
    if(iterator == readOwners.end()) {
        printf("readlock trace2\n");
        readOwners[mytid] = 1;
    } else {
        printf("readlock trace3 \n");
        iterator->second++;
    }
    return 0;
}

int _ReadWriteLock::_unReadlock() {
    AutoLock l(mMutex);
    int mytid = st(System)::myTid();
    auto iterator = readOwners.find(mytid);
    if(iterator == readOwners.end()) {
        return -1;
    }

    iterator->second--;
    if(iterator->second == 0) {
        readOwners.erase(iterator);
    }

    if(readOwners.size() == 0 && mWriteCount > 0) {
        mWriteCondition->notify();
    }

    return 0;
}

int _ReadWriteLock::_tryReadLock() {
    AutoLock l(mMutex);
    int mytid = st(System)::myTid();
    if(mWrOwner == mytid || mIsWrite == false) {
        return _readlock();
    }
    return -1;
}

int _ReadWriteLock::_readlock() {
    return _readlock(0);
}

int _ReadWriteLock::_writelock(long interval) {
    AutoLock l(mMutex);
    mWriteCount++;

    //check whether owner is myself
    int mytid = st(System)::myTid();
    auto iterator = readOwners.find(mytid);
    if(mWrOwner == mytid) {
        return 0;
    }
    printf("trace1,readOwners.size() is %d \n",readOwners.size());
    if(mIsWrite) {
        printf("mIsWrite is true \n");
    } else {
        printf("mIsWrite is false \n");
    }

    if(iterator == readOwners.end()) {
        printf("cannot find tid \n");
    } else {
        printf("find tid \n");
    }

    if(!mIsWrite && readOwners.size() == 1 && iterator != readOwners.end()) {
        printf("trace2 \n");
        goto end;
    }

    while(readOwners.size() != 0 || mIsWrite) {
        int ret = mWriteCondition->wait(mMutex,interval);
        if(ret != 0) {
            return ret;
        }
    }

end:
    mIsWrite = true;
    mWrOwner = mytid;
    return 0;
}

int _ReadWriteLock::_unWritelock() {
    AutoLock l(mMutex);
    int mytid = st(System)::myTid();

    if(mytid != mWrOwner) {
        return -1;
    }

    mIsWrite = false;
    mWrOwner = -1;
    mWriteCount--;
    if(mWriteCount == 0) {
        mReadCondition->notifyAll();
    } else {
        mWriteCondition->notify();
    }
    return 0;
}

int _ReadWriteLock::_tryWriteLock() {
    AutoLock l(mMutex);
    int mytid = st(System)::myTid();
    if(mWrOwner == mytid || mIsWrite == false) {
        if(readOwners.size() != 0) {
            return _readlock();
        }
    }
    return -1;
}

int _ReadWriteLock::_writelock() {
    return _writelock(0);
}

} // namespace obotcha
