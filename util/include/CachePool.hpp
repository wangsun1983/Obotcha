#ifndef __CACHE_POOL_HPP__
#define __CACHE_POOL_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ArrayList.hpp"
#include "Mutex.hpp"
#include "AutoMutex.hpp"
#include "Condition.hpp"

namespace obotcha {

DECLARE_CLASS(CachePool,1) {

enum CachePoolType {
    CachePoolTypeSync,
    CachePoolTypeASync
};


public:
    _CachePool(int size,int type = CachePoolTypeASync,int timeout = -1) {
        mCaches = createArrayList<T>();
        mSize = size;
        mMutex = createMutex("CachePool");
        if(type == CachePoolTypeSync) {
            mCondtion = createCondition();
        }
        mType = type;

        mTimeout = timeout;
    }

    int addCache(T t) {
        AutoMutex l(mMutex);
        if(mCaches->size() < mSize) {
            mCaches->add(t);
            if(mType == CachePoolTypeSync) {
                mCondtion->notify();
            }
            return 0;
        }

        return  -1;
    }

    T getCache() {
        AutoMutex l(mMutex);
        if(mCaches->size()!= 0) {
            return mCaches->remove(0);
        }

        if(mType == CachePoolTypeSync) {
            while(mCaches->size()!= 0) {
                if(mTimeout == -1) {
                    mCondtion->wait(mMutex);
                } else {
                    mCondtion->wait(mMutex,mTimeout);
                }

                return mCaches->remove(0);
            }
        }
        
        return nullptr;
    }

private:
    Mutex mMutex;
    Condition mCondtion;
    ArrayList<T> mCaches;
    int mSize;
    int mType;
    int mTimeout;
};

}


#endif