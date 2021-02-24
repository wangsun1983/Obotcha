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

namespace obotcha {

#define BLOCK_QUEUE_ADD_NOLOCK(Action) \
while(!isDestroy) {\
        int size = mQueue.size();\
        if(mCapacity > 0 && size == mCapacity) {\
            if(-WaitTimeout == mEnqueueCond->wait(mMutex,timeout)) {\
                return false;\
            }\
            continue;\
        }\
        Action;\
        mDequeueCond->notify();\
        return true;\
}\
return false;

#define BLOCK_QUEUE_ADD(Action) \
AutoLock l(mMutex);\
while(!isDestroy) {\
        int size = mQueue.size();\
        if(mCapacity > 0 && size == mCapacity) {\
            if(-WaitTimeout == mEnqueueCond->wait(mMutex,timeout)) {\
                return false;\
            }\
            continue;\
        }\
        Action;\
        mDequeueCond->notify();\
        return true;\
}\
return false;

#define BLOCK_QUEUE_REMOVE(Action) \
T ret;\
AutoLock l(mMutex);\
while(!isDestroy) {\
        int size = mQueue.size();\
        if(size == 0) {\
            if(-WaitTimeout == mDequeueCond->wait(mMutex,timeout)) {\
                return nullptr;\
            }\
            continue;\
        }\
        Action\
        mEnqueueCond->notify();\
        return ret;\
}\
return nullptr;

#define BLOCK_QUEUE_REMOVE_NOBLOCK(Action) \
T ret;\
AutoLock l(mMutex);\
while(!isDestroy) {\
    int size = mQueue.size();\
    if(size == 0) {\
        return nullptr;\
    }\
    Action\
    mEnqueueCond->notify();\
    break;\
}\
return ret;

class _ThreadPoolExecutor;

DECLARE_CLASS(BlockingQueue,1) {
public:
    friend class _ThreadPoolExecutor;
    friend class _ThreadCachedPoolExecutor;
    
	_BlockingQueue(int size);
    _BlockingQueue();

    inline int size();

    inline bool enQueueFirstNoLock(T val);
    inline bool enQueueLastNoLock(T val);
    inline bool enQueueFirstNoLock(T val,long timeout);
    inline bool enQueueLastNoLock(T val,long timeout);

    inline bool enQueueFirst(T val);
    inline bool enQueueLast(T val);

    inline bool enQueueFirst(T val,long timeout);
    inline bool enQueueLast(T val,long timeout);

    //dequeue
    inline T deQueueFirst();
    inline T deQueueLast();

    inline T deQueueFirst(long timeout);
    inline T deQueueLast(long timeout);

    //add interface for async
    inline T deQueueFirstNoBlock();
    inline T deQueueLastNoBlock();

    //destroy
    inline void destroy();

    ~_BlockingQueue();

    inline void clear();

private:
    std::vector<T> mQueue;
    int mCapacity;

    Mutex mMutex;
    Condition mEnqueueCond;
    Condition mDequeueCond;
    bool isDestroy;
};

template <typename T>
_BlockingQueue<T>::~_BlockingQueue() {
}

template <typename T>
_BlockingQueue<T>::_BlockingQueue(int size):mCapacity(size){
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
bool _BlockingQueue<T>::enQueueFirst(T val) {
    return enQueueFirst(val,0);
}

template <typename T>
bool _BlockingQueue<T>::enQueueFirst(T val,long timeout) {
    BLOCK_QUEUE_ADD(mQueue.insert(mQueue.begin(),val));
}

template <typename T>
bool _BlockingQueue<T>::enQueueLast(T val) {
    return enQueueLast(val,0);
}

template <typename T>
bool _BlockingQueue<T>::enQueueLast(T val,long timeout) {
    BLOCK_QUEUE_ADD(mQueue.push_back(val));
}

template <typename T>
T _BlockingQueue<T>::deQueueFirst() {
    return deQueueFirst(0);
}

template <typename T>
T _BlockingQueue<T>::deQueueFirst(long timeout) {
    BLOCK_QUEUE_REMOVE({
        ret = mQueue.at(0);
        mQueue.erase(mQueue.begin());
    });
}

template <typename T>
T _BlockingQueue<T>::deQueueLast() {
    return deQueueLast(0);
}

template <typename T>
T _BlockingQueue<T>::deQueueLast(long timeout) {
    BLOCK_QUEUE_REMOVE({
        T ret = mQueue.back();
        mQueue.pop_back();
    });
}

template <typename T>
T _BlockingQueue<T>::deQueueFirstNoBlock() {
    BLOCK_QUEUE_REMOVE_NOBLOCK({
        ret = mQueue.at(0);
        mQueue.erase(mQueue.begin());
    });
}

template <typename T>
T _BlockingQueue<T>::deQueueLastNoBlock() {
    BLOCK_QUEUE_REMOVE_NOBLOCK({
        ret = mQueue.back();
        mQueue.pop_back();
    });
}

template <typename T>
bool _BlockingQueue<T>::enQueueFirstNoLock(T val) {
    return enQueueFirstNoLock(val,0);
}

template <typename T>
bool _BlockingQueue<T>::enQueueLastNoLock(T val) {
    return enQueueLastNoLock(val,0);
}

template <typename T>
bool _BlockingQueue<T>::enQueueFirstNoLock(T val,long timeout) {
    BLOCK_QUEUE_ADD_NOLOCK(mQueue.insert(mQueue.begin(),val));
}

template <typename T>
bool _BlockingQueue<T>::enQueueLastNoLock(T val,long timeout) {
    BLOCK_QUEUE_ADD_NOLOCK(mQueue.push_back(val));
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