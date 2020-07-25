#ifndef __OBOTCHA_CACHE_POOL_HPP__
#define __OBOTCHA_CACHE_POOL_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ArrayList.hpp"
#include "Mutex.hpp"
#include "AutoLock.hpp"
#include "Condition.hpp"
#include "LinkedList.hpp"

namespace obotcha {

enum CachePoolType {
    CachePoolTypeSync = 0,
    CachePoolTypeASync
};

DECLARE_CLASS(CachePool,1) {
public:

    _CachePool(int size,int type = CachePoolTypeASync,int timeout = -1) {
        //mCaches = createArrayList<T>();
        mCaches = createLinkedList<T>();
        mSize = size;
        mMutex = createMutex("CachePool");
        if(type == CachePoolTypeSync) {
            mCondtion = createCondition();
        }
        mType = type;

        mTimeout = timeout;
    }

    int add(T t) {
        AutoLock l(mMutex);
        if(mCaches->size() < mSize) {
            mCaches->enQueueLast(t);
            if(mType == CachePoolTypeSync) {
                mCondtion->notify();
            }
            return 0;
        }

        return  -1;
    }

    T get() {
        while(1) {
            AutoLock l(mMutex);
            if(mCaches->size()!= 0) {
                return mCaches->deQueueFirst();
            }

            if(mType == CachePoolTypeSync) {
                if(mTimeout == -1) {
                    mCondtion->wait(mMutex);
                } else {
                    mCondtion->wait(mMutex,mTimeout);
                }
                continue;
            }

            break;
        }
        
        return nullptr;
    }

    int size() {
        AutoLock l(mMutex);
        return mCaches->size();
    }

private:
    Mutex mMutex;
    Condition mCondtion;
    //ArrayList<T> mCaches;
    LinkedList<T> mCaches;
    int mSize;
    int mType;
    int mTimeout;
};

}


#endif