#ifndef __OBOTCHA_CACHE_POOL_HPP__
#define __OBOTCHA_CACHE_POOL_HPP__

#include "Object.hpp"
#include "ArrayList.hpp"
#include "Mutex.hpp"
#include "AutoLock.hpp"
#include "Condition.hpp"
#include "LinkedList.hpp"

namespace obotcha {

DECLARE_CLASS(CachePool,1) {
public:

    _CachePool(int capacity = 32,int type = Global::ASync,int timeout = -1) {
        mCaches = createLinkedList<T>();
        mCapacity = capacity;
        mMutex = createMutex("CachePool");
        if(type == Global::Sync) {
            mCondition = createCondition();
        }
        mType = type;
        mTimeout = timeout;
    }

    int enqueue(T t) {
        AutoLock l(mMutex);
        while(1) {
            if(mCaches->size() < mCapacity) {
                mCaches->enQueueLast(t);
                if(mType == Global::Sync) {
                    mCondition->notify();
                }
                return 0;
            } else {
                if(mType == Global::Sync) {
                    mCondition->wait(mMutex);
                    continue;
                }
                return -1;
            }
        }
    }

    T dequeue() {
        while(1) {
            AutoLock l(mMutex);
            if(mCaches->size()!= 0) {
                return mCaches->deQueueFirst();
            }

            if(mType == Global::Sync) {
                if(mTimeout == -1) {
                    mCondition->wait(mMutex);
                    continue;
                } else {
                    mCondition->wait(mMutex,mTimeout);
                }
            }

            break;
        }
        
        return nullptr;
    }

    int size() {
        AutoLock l(mMutex);
        return mCaches->size();
    }

    int capacity() {
        return mCapacity;
    }

private:
    Mutex mMutex;
    Condition mCondition;
    LinkedList<T> mCaches;
    int mCapacity;
    int mType;
    int mTimeout;
};

}


#endif