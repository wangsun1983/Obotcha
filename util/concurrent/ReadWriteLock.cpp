#include "ReadWriteLock.hpp"
#include "Process.hpp"
#include "Log.hpp"

namespace obotcha {

//------------ ReadLock ------------
_ReadLock::_ReadLock(sp<_ReadWriteLock> l, String s):rwlock(l),mName(s) {    
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
_WriteLock::_WriteLock(sp<_ReadWriteLock> l, String s):rwlock(l),mName(s) {
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
_ReadWriteLock::_ReadWriteLock(String s):mName(s) {
}

sp<_ReadLock> _ReadWriteLock::getReadLock() {
    return AutoClone(new _ReadLock(AutoClone(this), mName));
}

sp<_WriteLock> _ReadWriteLock::getWriteLock() {
    return AutoClone(new _WriteLock(AutoClone(this), mName));
}

bool _ReadWriteLock::isOwner() {
    auto tid = st(Process)::MyTid();
    AutoLock l(mMutex);
    return (mWrOwner == tid || mReadOwners.find(tid) != mReadOwners.end());
}

String _ReadWriteLock::getName() { 
    return mName; 
}

int _ReadWriteLock::_readlock(long interval) {
    auto mytid = st(Process)::MyTid();
    AutoLock l(mMutex);
    while(mWrOwnerCount != 0 && mytid != mWrOwner) {
        int ret = mReadCondition->wait(mMutex,interval);
        Inspect(ret != 0,ret)
    }

    auto iterator = mReadOwners.find(mytid);
    if(iterator == mReadOwners.end()) {
        mReadOwners[mytid] = 1;
    } else {
        iterator->second++;
    }
    return 0;
}

int _ReadWriteLock::_unReadlock() {
    auto mytid = st(Process)::MyTid();
    
    AutoLock l(mMutex);
    auto iterator = mReadOwners.find(mytid);
    Inspect(iterator == mReadOwners.end(),-1)

    iterator->second--;
    if(iterator->second == 0) {
        mReadOwners.erase(iterator);
    }

    if(mReadOwners.size() == 0 && mWriteReqCount > 0) {
        mWriteCondition->notify();
    }

    return 0;
}

int _ReadWriteLock::_tryReadLock() {
    auto mytid = st(Process)::MyTid();
    AutoLock l(mMutex);
    return (mWrOwner == mytid || mIsWrite == false)?
                _readlock(0):-EBUSY;
}

int _ReadWriteLock::_writelock(long interval) {
    auto mytid = st(Process)::MyTid();
    AutoLock l(mMutex);
    //check whether owner is myself
    if(mWrOwner == mytid) {
        mWrOwnerCount++;
        return 0;
    }

    if(!mIsWrite) {
        if(mReadOwners.find(mytid) != mReadOwners.end() 
            && mReadOwners.size() == 1) {
            mWrOwnerCount++;
            goto end;
        }
    }

    mWriteReqCount++;
    while(!mReadOwners.empty() || mIsWrite) {
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
    auto mytid = st(Process)::MyTid();

    AutoLock l(mMutex);
    Inspect(mytid != mWrOwner,-1)
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
    auto mytid = st(Process)::MyTid();

    AutoLock l(mMutex);
    if(mWrOwner == mytid) {
        return _writelock(0);
    }

    if(mReadOwners.size() == 1) {
        auto iterator = mReadOwners.find(mytid);
        if(iterator != mReadOwners.end()) {
            return _writelock(0);
        }
    }

    if(mReadOwners.empty() && !mIsWrite) {
        return _writelock(0);
    }

    return -EBUSY;
}

} // namespace obotcha
