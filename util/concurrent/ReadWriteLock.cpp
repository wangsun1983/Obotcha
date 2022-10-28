#include <pthread.h>

#include "Error.hpp"
#include "ReadWriteLock.hpp"
#include "Process.hpp"
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
    mWrOwnerCount = 0;
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
    int tid = st(Process)::myTid();
    return (mWrOwner == tid || readOwners.find(tid) != readOwners.end());
}

String _ReadWriteLock::getName() { 
    return mName; 
}

_ReadWriteLock::~_ReadWriteLock() { 
    //nothing
}

int _ReadWriteLock::_readlock(long interval) {
    AutoLock l(mMutex);
    int mytid = st(Process)::myTid();
    while(mWrOwnerCount != 0 && mytid != mWrOwner) {
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
    int mytid = st(Process)::myTid();
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
    int mytid = st(Process)::myTid();
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
    int mytid = st(Process)::myTid();
    if(mWrOwner == mytid) {
        mWrOwnerCount++;
        return 0;
    }

    if(!mIsWrite) {
        auto iterator = readOwners.find(mytid);
        if(iterator != readOwners.end() && readOwners.size() == 1) {
            mWrOwnerCount++;
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
    mWrOwnerCount++;
end:
    mIsWrite = true;
    mWrOwner = mytid;
    return 0;
}

int _ReadWriteLock::_unWritelock() {
    AutoLock l(mMutex);
    int mytid = st(Process)::myTid();
    if(mytid != mWrOwner) {
        return -1;
    }
    
    mWrOwnerCount--;
    
    if(mWrOwnerCount == 0) {
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
    int mytid = st(Process)::myTid();

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
