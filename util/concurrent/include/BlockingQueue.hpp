#ifndef __BLOCKING_QUEUE_HPP__
#define __BLOCKING_QUEUE_HPP__

#include <vector>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "AutoMutex.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"

#include "Boolean.hpp"
#include "Double.hpp"
#include "Float.hpp"
#include "Integer.hpp"
#include "InitializeException.hpp"

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

    //int
    inline void enQueueFirst(int val);
    inline void enQueueLast(int val);

    inline bool enQueueFirst(int val,long timeout);
    inline bool enQueueLast(int val,long timeout);

    //bool
    inline void enQueueFirst(bool val);
    inline void enQueueLast(bool val);

    inline bool enQueueFirst(bool val,long timeout);
    inline bool enQueueLast(bool val,long timeout);

    //double
    inline void enQueueFirst(double val);
    inline void enQueueLast(double val);

    inline bool enQueueFirst(double val,long timeout);
    inline bool enQueueLast(double val,long timeout);

    //float
    inline void enQueueFirst(float val);
    inline void enQueueLast(float val);

    inline bool enQueueFirst(float val,long timeout);
    inline bool enQueueLast(float val,long timeout);    

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

    //wait for empty
    //inline void waitForEmpty();
    //inline void waitForEmpty(long timeout);

    inline void clear();

private:
    vector<T> mQueue;
    int mCapacity;

    //pthread_mutex_t mMutex;
    //pthread_cond_t mEnqueueCond;

    //pthread_mutex_t mOutMutex;
    //pthread_cond_t mDequeueCond;
    Mutex mMutex;
    Condition mEnqueueCond;
    Condition mDequeueCond;
    bool isDestroy;
};

template <typename T>
_BlockingQueue<T>::~_BlockingQueue() {
    AutoMutex l(mMutex);
    isDestroy = true;
    mEnqueueCond->notify();
    mDequeueCond->notify();
}

//template class/function must be defined in hpp file.
template <typename T>
_BlockingQueue<T>::_BlockingQueue(int size):mCapacity(size){
    if(size == 0) {
        throw InitializeException(createString("BlockingQueue size is 0"));
    }

    mMutex = createMutex("BlockingQueueMutex");
    mEnqueueCond = createCondition();
    mDequeueCond = createCondition();
    isDestroy = false;
    mCapacity = size;
}

template <typename T>
_BlockingQueue<T>::_BlockingQueue() {
    mMutex = createMutex("BlockingQueueMutex2");
    mEnqueueCond = createCondition();
    mDequeueCond = createCondition();
    isDestroy = false;
    mCapacity = -1;
}

template <typename T>
void _BlockingQueue<T>::enQueueFirst(T val) {
    while(1) {
        AutoMutex l(mMutex);
        int size = mQueue.size();
        if(mCapacity != -1 && size == mCapacity) {
            mEnqueueCond->wait(mMutex);
            if(isDestroy) {
                return;
            }
            continue;
        }

        mQueue.insert(mQueue.begin(),val);
        break;
    }
    
    mDequeueCond->notify();
}

template <typename T>
bool _BlockingQueue<T>::enQueueFirst(T val,long timeout) {
    int waitCount = 0;

    while(1) {
        AutoMutex l(mMutex);
        int size = mQueue.size();
        if(mCapacity != -1 && size == mCapacity) {
            if(waitCount == 1) {
                return false;
            }

            mEnqueueCond->wait(mMutex,timeout);
            if(isDestroy) {
                return false;
            }
            waitCount++;
            continue;
        }

        mQueue.insert(mQueue.begin(),val);
        break;
    }
    
    mDequeueCond->notify();

    return true;
}

template <typename T>
void _BlockingQueue<T>::enQueueLast(T val) {
    while(1) {
        AutoMutex l(mMutex);
        int size = mQueue.size();
        if(mCapacity != -1 && size == mCapacity) {
            mEnqueueCond->wait(mMutex);
            if(isDestroy) {
                return;
            }
            continue;
        }
    
        mQueue.push_back(val);
        break;
    }

    mDequeueCond->notify();
}

template <typename T>
bool _BlockingQueue<T>::enQueueLast(T val,long timeout) {
    int waitCount = 0;

    while(1) {
        AutoMutex l(mMutex);
    
        int size = mQueue.size();
        if(mCapacity != -1 && size == mCapacity) {
            if(waitCount == 1) {
                return false;
            }

            mEnqueueCond->wait(mMutex,timeout);
            if(isDestroy) {
                return false;
            }
            waitCount++;
            continue;
        }
    
        mQueue.push_back(val);
        break;
    }

    mDequeueCond->notify();
    return true;
}

template <typename T>
bool _BlockingQueue<T>::remove(T val) {
    AutoMutex l(mMutex);
    int size = mQueue.size();
    for(int i = 0;i<size;i++) {
        T t = mQueue.at(0);
        if(t == val) {
            mQueue.erase(mQueue.begin() + i);
            return true;
        }
    }

    return false;
}


template <typename T>
void _BlockingQueue<T>::enQueueFirst(int val) {
    Integer v = createInteger(val);
    enQueueFirst(v);
}

template <typename T>
bool _BlockingQueue<T>::enQueueFirst(int val,long timeout) {
    Integer v = createInteger(val);
    return enQueueFirst(v,timeout);
}

template <typename T>
void _BlockingQueue<T>::enQueueLast(int val) {
    Integer v = createInteger(val);
    enQueueLast(v);
}

template <typename T>
bool _BlockingQueue<T>::enQueueLast(int val,long timeout) {
    Integer v = createInteger(val);
    return enQueueLast(v,timeout);
}


template <typename T>
void _BlockingQueue<T>::enQueueFirst(bool val) {
    Boolean v = createBoolean(val);
    enQueueFirst(v);
}

template <typename T>
bool _BlockingQueue<T>::enQueueFirst(bool val,long timeout) {
    Boolean v = createBoolean(val);
    return enQueueFirst(v,timeout);
}

template <typename T>
void _BlockingQueue<T>::enQueueLast(bool val) {
    Boolean v = createBoolean(val);
    enQueueLast(v);
}

template <typename T>
bool _BlockingQueue<T>::enQueueLast(bool val,long timeout) {
    Boolean v = createBoolean(val);
    return enQueueLast(v,timeout);
}

template <typename T>
void _BlockingQueue<T>::enQueueFirst(double val) {
    Double v = createDouble(val);
    enQueueFirst(v);
}

template <typename T>
bool _BlockingQueue<T>::enQueueFirst(double val,long timeout) {
    Double v = createDouble(val);
    return enQueueFirst(v,timeout);
}

template <typename T>
void _BlockingQueue<T>::enQueueLast(double val) {
    Double v = createDouble(val);
    enQueueLast(v);
}

template <typename T>
bool _BlockingQueue<T>::enQueueLast(double val,long timeout) {
    Double v = createDouble(val);
    return enQueueLast(v,timeout);
}

template <typename T>
void _BlockingQueue<T>::enQueueFirst(float val) {
    Float v = createFloat(val);
    enQueueFirst(v);
}

template <typename T>
bool _BlockingQueue<T>::enQueueFirst(float val,long timeout) {
    Float v = createFloat(val);
    return enQueueFirst(v,timeout);
}

template <typename T>
void _BlockingQueue<T>::enQueueLast(float val) {
    Float v = createFloat(val);
    enQueueLast(v);
}

template <typename T>
bool _BlockingQueue<T>::enQueueLast(float val,long timeout) {
    Float v = createFloat(val);
    return enQueueLast(v,timeout);
}

template <typename T>
T _BlockingQueue<T>::deQueueFirst() {
    T ret;
    while(1) {
        AutoMutex l(mMutex);
        int size = mQueue.size();
        if(size == 0) {
            if(isDestroy) {
                return nullptr;
            }
            
            mDequeueCond->wait(mMutex);
            if(isDestroy) {
                return nullptr;
            }
            continue;
        }

        ret = mQueue.at(0);
        mQueue.erase(mQueue.begin());
        
        break;
    }

    mEnqueueCond->notify();
    return ret;
}

template <typename T>
T _BlockingQueue<T>::deQueueFirst(long timeout) {
    T ret;

    while(1) {
        AutoMutex l(mMutex);
        int size = mQueue.size();
        if(size == 0) {
            if(NotifyByTimeout == mDequeueCond->wait(mMutex,timeout)) {
                return nullptr;
            } 

            if(isDestroy) {
                return nullptr;
            }
            continue;
        }
        ret = mQueue.at(0);
        mQueue.erase(mQueue.begin());
        
        break;
    }

    mEnqueueCond->notify();
    return ret;
}

template <typename T>
T _BlockingQueue<T>::deQueueLast() {
    T ret;

    while(1) {
        AutoMutex l(mMutex);
        if(isDestroy) {
            return nullptr;
        }

        int size = mQueue.size();
        
        if(size == 0) {
            mDequeueCond->wait(mMutex);
            if(isDestroy) {
                return nullptr;
            }
            continue;
        }

        ret = mQueue.back();
        mQueue.pop_back();
        break;
    }

    return ret;
}

template <typename T>
T _BlockingQueue<T>::deQueueLast(long interval) {
    T ret;
    while(1) {
        AutoMutex l(mMutex);
        int size = mQueue.size();
        
        if(size == 0) {
            if(NotifyByTimeout == mDequeueCond->wait(mMutex,interval)) {
                return nullptr;
            }

            if(isDestroy) {
                return nullptr;
            }
            continue;
        }

        ret = mQueue.back();
        mQueue.pop_back();
        break;
    }

    return ret;
}

//wangsl
template <typename T>
T _BlockingQueue<T>::deQueueFirstNoBlock() {
    T ret;
    while(1) {
        AutoMutex l(mMutex);
        int size = mQueue.size();
        if(size == 0) {
            return nullptr;
        }

        ret = mQueue.at(0);
        mQueue.erase(mQueue.begin());
        
        break;
    }

    mEnqueueCond->notify();
    return ret;
}

template <typename T>
T _BlockingQueue<T>::deQueueFirstNoBlock(long timeout) {
    T ret;
    int waitCount = 0;

    while(1) {
        AutoMutex l(mMutex);
        int size = mQueue.size();
        if(size == 0) {
            return nullptr;
        }

        ret = mQueue.at(0);
        mQueue.erase(mQueue.begin());
        
        break;
    }

    mEnqueueCond->notify();
    return ret;
}

template <typename T>
T _BlockingQueue<T>::deQueueLastNoBlock() {
    T ret;

    while(1) {
        AutoMutex l(mMutex);
        int size = mQueue.size();
        
        if(size == 0) {
            return nullptr;
        }

        ret = mQueue.back();
        mQueue.pop_back();
        break;
    }

    return ret;
}

template <typename T>
T _BlockingQueue<T>::deQueueLastNoBlock(long interval) {
    T ret;
    int waitCount = 0;

    while(1) {
        AutoMutex l(mMutex);
        int size = mQueue.size();
        
        if(size == 0) {
            return nullptr;
        }

        ret = mQueue.back();
        mQueue.pop_back();
        break;
    }

    return ret;
}

template <typename T>
int _BlockingQueue<T>::size() {
    AutoMutex l(mMutex);
    return mQueue.size();
}

template <typename T>
void _BlockingQueue<T>::clear() {
    AutoMutex l(mMutex);
    mQueue.clear();
}

template <typename T>
void _BlockingQueue<T>::destroy() {
    AutoMutex l(mMutex);
    isDestroy = true;
    mQueue.clear();
    mEnqueueCond->notifyAll();
    mDequeueCond->notifyAll();
}


}
#endif