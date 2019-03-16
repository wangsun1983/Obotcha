#ifndef __BLOCKING_QUEUE_HPP__
#define __BLOCKING_QUEUE_HPP__

#include <vector>
#include <pthread.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "AutoMutex.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"

#include "Boolean.hpp"
#include "Double.hpp"
#include "Float.hpp"
#include "Integer.hpp"

using namespace std;

namespace obotcha {

DECLARE_CLASS(BlockingQueue,1) {
public:
	_BlockingQueue(int size);
    _BlockingQueue();

    inline int size();

    inline void enQueueFirst(T val);
    inline void enQueueLast(T val);

    //int
    inline void enQueueFirst(int val);
    inline void enQueueLast(int val);

    //bool
    inline void enQueueFirst(bool val);
    inline void enQueueLast(bool val);

    //double
    inline void enQueueFirst(double val);
    inline void enQueueLast(double val);

    //float
    inline void enQueueFirst(float val);
    inline void enQueueLast(float val);

    inline T deQueueFirst();
    inline T deQueueLast();

    inline void waitForEmpty();

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
};

//template class/function must be defined in hpp file.
template <typename T>
_BlockingQueue<T>::_BlockingQueue(int size):mCapacity(size){
    mMutex = createMutex();
    mEnqueueCond = createCondition();
    mDequeueCond = createCondition();
}

template <typename T>
_BlockingQueue<T>::_BlockingQueue() {
    mMutex = createMutex();
    mEnqueueCond = createCondition();
    mDequeueCond = createCondition();
    mCapacity = -1;
}

template <typename T>
void _BlockingQueue<T>::enQueueFirst(T val) {
    AutoMutex l(mMutex);
    int size = mQueue.size();
    if(mCapacity != -1 && size == mCapacity) {
        //pthread_cond_wait(&mEnqueueCond, &mMutex);
        mEnqueueCond->wait(mMutex);
    }

    mQueue.insert(mQueue.begin(),val);

    if(size == 0 || size == mCapacity) {
        //pthread_cond_signal(&mDequeueCond);
        mDequeueCond->notify();
    }
}

template <typename T>
void _BlockingQueue<T>::enQueueLast(T val) {
    //printf("enqueuelast \n");
    AutoMutex l(mMutex);
    //printf("enqueuelast1 \n");
    int size = mQueue.size();
    if(mCapacity != -1 && size == mCapacity) {
        //pthread_cond_wait(&mEnqueueCond, &mMutex);
        //printf("enqueuelast2 \n");
        mEnqueueCond->wait(mMutex);
    }
    //printf("enqueuelast3 \n");
    mQueue.push_back(val);

    if(size == 0 || size == mCapacity) {
        //pthread_cond_wait(&mCond, &mMutex);
        //pthread_cond_signal(&mDequeueCond);
        mDequeueCond->notify();
    }
}

template <typename T>
void _BlockingQueue<T>::enQueueFirst(int val) {
    Integer v = createInteger(val);
    enQueueFirst(v);
}

template <typename T>
void _BlockingQueue<T>::enQueueLast(int val) {
    Integer v = createInteger(val);
    enQueueLast(v);
}

template <typename T>
void _BlockingQueue<T>::enQueueFirst(bool val) {
    Boolean v = createBoolean(val);
    enQueueFirst(v);
}

template <typename T>
void _BlockingQueue<T>::enQueueLast(bool val) {
    Boolean v = createBoolean(val);
    enQueueLast(v);
}

template <typename T>
void _BlockingQueue<T>::enQueueFirst(double val) {
    Double v = createDouble(val);
    enQueueFirst(v);
}

template <typename T>
void _BlockingQueue<T>::enQueueLast(double val) {
    Double v = createDouble(val);
    enQueueLast(v);
}

template <typename T>
void _BlockingQueue<T>::enQueueFirst(float val) {
    Float v = createFloat(val);
    enQueueFirst(v);
}

template <typename T>
void _BlockingQueue<T>::enQueueLast(float val) {
    Float v = createFloat(val);
    enQueueLast(v);
}

template <typename T>
T _BlockingQueue<T>::deQueueFirst() {
    //printf("wangsl,deQueueFirst \n");
    AutoMutex l(mMutex);

    int size = mQueue.size();
    //printf("wangsl,deQueueFirst1 \n");
    if(size == 0) {
        //pthread_cond_wait(&mDequeueCond, &mMutex);
        //printf("wangsl,deQueueFirst2,mutex_t is %x \n",mMutex->getMutex_t());
        mDequeueCond->wait(mMutex);
    }

    T ret = mQueue.at(0);
    mQueue.erase(mQueue.begin());

    if(size == mCapacity || size == 0) {
        //pthread_cond_signal(&mEnqueueCond);
        mEnqueueCond->notify();
    }

    return ret;
}

template <typename T>
T _BlockingQueue<T>::deQueueLast() {
    AutoMutex l(mMutex);
    int size = mQueue.size();
    if(size == 0) {
        //pthread_cond_wait(&mDequeueCond, &mMutex);
        mDequeueCond->wait(mMutex);
    }

    //T ret = mQueue.pop_back();
    T ret = mQueue.back();
    mQueue.pop_back();

    if(size == mCapacity || size == 0) {
        //pthread_cond_signal(&mEnqueueCond);
        mEnqueueCond->notify();
    }

    return ret;
}

template <typename T>
int _BlockingQueue<T>::size() {
    AutoMutex l(mMutex);
    return mQueue.size();
}

}
#endif