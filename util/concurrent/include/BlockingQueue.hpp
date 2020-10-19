#ifndef __OBOTCHA_BLOCKING_QUEUE_HPP__
#define __OBOTCHA_BLOCKING_QUEUE_HPP__

#include <vector>
#include <unistd.h>
#include <errno.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "AutoLock.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "InitializeException.hpp"
#include "Error.hpp"
#include "System.hpp"

using namespace std;

namespace obotcha {

DECLARE_CLASS(BlockingQueue,1) {
public:
	_BlockingQueue(int size);
    _BlockingQueue();

    inline int size();

    inline void enQueueFirst(T val);
    inline void enQueueLast(T val);

    inline bool enQueueFirst(T val,long timeout);
    inline bool enQueueLast(T val,long timeout);

    inline bool remove(T val);

    //dequeue
    inline T deQueueFirst();
    inline T deQueueLast();

    inline T deQueueFirst(long timeout);
    inline T deQueueLast(long timeout);

    //add interface for async
    inline T deQueueFirstNoBlock();
    inline T deQueueLastNoBlock();

    inline T deQueueFirstNoBlock(long timeout);
    inline T deQueueLastNoBlock(long timeout);

    //destroy
    inline void destroy();

    ~_BlockingQueue();

    inline void clear();

private:
    vector<T> mQueue;
    int mCapacity;

    Mutex mMutex;
    Condition mEnqueueCond;
    Condition mDequeueCond;
    bool isDestroy;
};

template <typename T>
_BlockingQueue<T>::~_BlockingQueue() {
    AutoLock l(mMutex);
    isDestroy = true;
    mEnqueueCond->notify();
    mDequeueCond->notify();
}

//template class/function must be defined in hpp file.
template <typename T>
_BlockingQueue<T>::_BlockingQueue(int size):mCapacity(size){
    if(size == 0) {
        throwInitializeException("BlockingQueue size is 0");
    }

    mMutex = createMutex("BlockingQueueMutex");
    mEnqueueCond = createCondition();
    mDequeueCond = createCondition();
    isDestroy = false;
    mCapacity = size;
}

template <typename T>
_BlockingQueue<T>::_BlockingQueue():_BlockingQueue(-1) {
    //Nothing
}

template <typename T>
void _BlockingQueue<T>::enQueueFirst(T val) {
    enQueueFirst(val,0);
}

template <typename T>
bool _BlockingQueue<T>::enQueueFirst(T val,long timeout) {
    while(1) {
        AutoLock l(mMutex);
        if(isDestroy) {
            return false;
        }

        int size = mQueue.size();
        if(mCapacity != -1 && size == mCapacity) {
            if(-WaitTimeout == mEnqueueCond->wait(mMutex,timeout)) {
                return false;
            }
            continue;
        }

        mQueue.insert(mQueue.begin(),val);
        mDequeueCond->notify();
        return true;
    }
    return false;
}

template <typename T>
void _BlockingQueue<T>::enQueueLast(T val) {
    enQueueLast(val,0);
}

template <typename T>
bool _BlockingQueue<T>::enQueueLast(T val,long timeout) {
    int waitCount = 0;

    while(1) {
        AutoLock l(mMutex);
        if(isDestroy) {
            return false;
        }

        int size = mQueue.size();
        if(mCapacity != -1 && size == mCapacity) {
            if(-WaitTimeout == mEnqueueCond->wait(mMutex,timeout)) {
                return false;
            }
            continue;
        }
    
        mQueue.push_back(val);
        mDequeueCond->notify();
        return true;
    }

    return false;
}

template <typename T>
bool _BlockingQueue<T>::remove(T val) {
    AutoLock l(mMutex);
    auto iterator = mQueue.begin();
    while(iterator != mQueue.end()) {
        if(*iterator == val) {
            iterator = mQueue.erase(iterator);
            continue;
        }
        iterator++;
    }

    return true;
}

template <typename T>
T _BlockingQueue<T>::deQueueFirst() {
    return deQueueFirst(0);
}

template <typename T>
T _BlockingQueue<T>::deQueueFirst(long timeout) {
    while(1) {
        AutoLock l(mMutex);
        if(isDestroy) {
            return nullptr;
        }

        int size = mQueue.size();
        if(size == 0) {
            if(-WaitTimeout == mDequeueCond->wait(mMutex,timeout)) {
                return nullptr;
            }
            continue;
        }

        T ret = mQueue.at(0);
        mQueue.erase(mQueue.begin());
        mEnqueueCond->notify();    
        return ret;
    }

    return nullptr;
}

template <typename T>
T _BlockingQueue<T>::deQueueLast() {
    return deQueueLast(0);
}

template <typename T>
T _BlockingQueue<T>::deQueueLast(long interval) {
    while(1) {
        AutoLock l(mMutex);
        if(isDestroy) {
            return nullptr;
        }

        int size = mQueue.size();
        if(size == 0) {
            if(-WaitTimeout == mDequeueCond->wait(mMutex,interval)) {
                return nullptr;
            }
            
            continue;
        }
        
        T ret = mQueue.back();
        mQueue.pop_back();
        mEnqueueCond->notify();
        return ret;
    }

    return nullptr;
}

//wangsl
template <typename T>
T _BlockingQueue<T>::deQueueFirstNoBlock() {
    T ret;
    while(1) {
        AutoLock l(mMutex);
        if(isDestroy) {
            return nullptr;
        }

        int size = mQueue.size();
        if(size == 0) {
            return nullptr;
        }

        ret = mQueue.at(0);
        mQueue.erase(mQueue.begin());
        mEnqueueCond->notify();   
        break;
    }
    return ret;
}

template <typename T>
T _BlockingQueue<T>::deQueueLastNoBlock() {
    T ret;

    while(1) {
        AutoLock l(mMutex);
        if(isDestroy) {
            return nullptr;
        }

        int size = mQueue.size();
        
        if(size == 0) {
            return nullptr;
        }

        ret = mQueue.back();
        mQueue.pop_back();
        mEnqueueCond->notify();
        break;
    }
    return ret;
}

template <typename T>
int _BlockingQueue<T>::size() {
    AutoLock l(mMutex);
    return mQueue.size();
}

template <typename T>
void _BlockingQueue<T>::clear() {
    AutoLock l(mMutex);
    mQueue.clear();
}

template <typename T>
void _BlockingQueue<T>::destroy() {
    AutoLock l(mMutex);
    isDestroy = true;
    mQueue.clear();
    mEnqueueCond->notifyAll();
    mDequeueCond->notifyAll();
}

}
#endif