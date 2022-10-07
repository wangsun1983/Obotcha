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
    mWriteReqCount = 0;
    mOwnerCount = 0;
    mIsWrite = false;
    mWrOwner = -1;

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

bool _ReadWriteLock::isOwner() {
    AutoLock l(mMutex);
    int tid = st(System)::myTid();
    return (mWrOwner == tid || readOwners.find(tid) != readOwners.end());
}

String _ReadWriteLock::getName() { 
    return mName; 
}

_ReadWriteLock::~_ReadWriteLock() { 
    
}

int _ReadWriteLock::_readlock(long interval) {
    AutoLock l(mMutex);
    int mytid = st(System)::myTid();
    while(mOwnerCount != 0 && mytid != mWrOwner) {
        int ret = mReadCondition->wait(mMutex,interval);
        if(ret != 0) {
            return ret;
        }
    }
    auto iterator = readOwners.find(mytid);
    if(iterator == readOwners.end()) {
        readOwners[mytid] = 1;
    } else {
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

    if(readOwners.size() == 0 && mWriteReqCount > 0) {
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
    return -EBUSY;
}

int _ReadWriteLock::_readlock() {
    return _readlock(0);
}

int _ReadWriteLock::_writelock(long interval) {
    AutoLock l(mMutex);
    //check whether owner is myself
    int mytid = st(System)::myTid();
    if(mWrOwner == mytid) {
        mOwnerCount++;
        return 0;
    }

    if(!mIsWrite) {
        auto iterator = readOwners.find(mytid);
        if(iterator != readOwners.end() && readOwners.size() == 1) {
            mOwnerCount++;
            goto end;
        }
    }

    mWriteReqCount++;
    while(readOwners.size() != 0 || mIsWrite) {
        int ret = mWriteCondition->wait(mMutex,interval);
        if(ret != 0) {
            mWriteReqCount--;
            return ret;
        }
    }
    mWriteReqCount--;
    mOwnerCount++;
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
    
    mOwnerCount--;
    
    if(mOwnerCount == 0) {
        mIsWrite = false;
        mWrOwner = -1;
        if(mWriteReqCount == 0) {
            mReadCondition->notifyAll();
        } else {
            mWriteCondition->notify();
        }
    } 
    return 0;
}

int _ReadWriteLock::_tryWriteLock() {
    AutoLock l(mMutex);
    int mytid = st(System)::myTid();

    if(mWrOwner == mytid) {
        return 0;
    }

    if(readOwners.size() == 1) {
        auto iterator = readOwners.find(mytid);
        if(iterator != readOwners.end()) {
            return 0;
        }
    }

    if(readOwners.size() == 0 && !mIsWrite) {
        return _writelock();
    }

    return -EBUSY;
}

int _ReadWriteLock::_writelock() {
    return _writelock(0);
}

} // namespace obotcha
