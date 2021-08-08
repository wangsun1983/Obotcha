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
#include "ContainerValue.hpp"

namespace obotcha {

#define BLOCK_QUEUE_ADD_NOLOCK(Action) \
if(!isDestroy) {\
        int size = mQueue.size();\
        if(mCapacity > 0 && size == mCapacity) {\
                return false;\
        }\
        Action;\
        notEmpty->notify();\
        return true;\
}\
return false;

#define BLOCK_QUEUE_ADD(Action) \
AutoLock l(mMutex);\
while(!isDestroy) {\
        int size = mQueue.size();\
        if(mCapacity > 0 && size == mCapacity) {\
            if(-WaitTimeout == notFull->wait(mMutex,timeout)) {\
                return false;\
            }\
            continue;\
        }\
        Action;\
        notEmpty->notify();\
        return true;\
}\
return false;

#define BLOCK_QUEUE_REMOVE(Action) \
T ret;\
AutoLock l(mMutex);\
while(!isDestroy) {\
    int size = mQueue.size();\
    if(size == 0) {\
        if(-WaitTimeout == notEmpty->wait(mMutex,timeout)) {\
            return ContainerValue<T>(nullptr).get();\
        }\
        continue;\
    }\
    Action\
    notFull->notify();\
    return ret;\
}\
return ContainerValue<T>(nullptr).get();

#define BLOCK_QUEUE_REMOVE_NOBLOCK(Action) \
T ret;\
AutoLock l(mMutex);\
if(!isDestroy) {\
    int size = mQueue.size();\
    if(size == 0) {\
        return ContainerValue<T>(nullptr).get();\
    }\
    Action\
    notFull->notify();\
}\
return ret;

DECLARE_CLASS(BlockingQueue,1) {
public:
	_BlockingQueue(int size) :mCapacity(size) {
        mMutex = createMutex("BlockingQueueMutex");
        notEmpty = createCondition();
        notFull = createCondition();
        isDestroy = false;
        mCapacity = size;
    }

    _BlockingQueue():_BlockingQueue(1024) {
    }

    ~_BlockingQueue() {}

    inline int size() {
        AutoLock l(mMutex);
        return mQueue.size();
    }

    inline int capacity() {
        return mCapacity;
    }

    inline void freeze() {
        mMutex->unlock();
    }

    inline void unfreeze() {
        mMutex->unlock();
    }

    /**
    * Retrieves and removes the head of the queue represented by this deque
    * (in other words, the first element of this deque), waiting if
    * necessary until an element becomes available.
    */
    inline bool putFirst(const T & val,long timeout = 0) {
        BLOCK_QUEUE_ADD(mQueue.insert(mQueue.begin(),val));
    }

    inline bool putLast(const T &val,long timeout = 0) {
        BLOCK_QUEUE_ADD(mQueue.emplace_back(val));
    }

    inline bool tryPutFirst(const T & val) {
        BLOCK_QUEUE_ADD_NOLOCK(mQueue.insert(mQueue.begin(),val));
    }

    inline bool tryPutLast(const T &val) {
        BLOCK_QUEUE_ADD_NOLOCK(mQueue.emplace_back(val));
    }

    /**
    * Retrieves and removes the first element of this deque, waiting
    * if necessary until an element becomes available.
    */
    inline T takeFirst(long timeout = 0) {
        BLOCK_QUEUE_REMOVE({
            ret = mQueue.at(0);
            mQueue.erase(mQueue.begin());
        });
    }

    inline T takeLast(long timeout = 0) {
        BLOCK_QUEUE_REMOVE({
            ret = mQueue.back();
            mQueue.pop_back();
        });
    }

    inline T tryTakeFirst() {
        BLOCK_QUEUE_REMOVE_NOBLOCK({
            ret = mQueue.at(0);
            mQueue.erase(mQueue.begin());
        });
    }

    inline T tryTakeLast() {
        BLOCK_QUEUE_REMOVE_NOBLOCK({
            ret = mQueue.back();
            mQueue.pop_back();
        });
    }

    /**
    * Retrieves, but does not remove, the head of the queue represented by
    * this deque (in other words, the first element of this deque), or
    * returns nullptr if this deque is empty.
    */
    inline T peekFirst() {
        AutoLock l(mMutex);
        return (mQueue.size() == 0)?nullptr:mQueue[0];
    }

    inline T peekLast() {
        AutoLock l(mMutex);
        return (mQueue.size() == 0)?nullptr:mQueue[mQueue.size() - 1];
    }

    //add foreach lambda
    using foreachCallback = std::function<int(T &)>;
    inline void foreach(foreachCallback callback) {
        AutoLock l(mMutex);
        for (T value:mQueue) {
            if(callback(value) == Global::Break) {
                break;
            }
        }
    }

    //destroy
    inline void destroy() {
        AutoLock l(mMutex);
        isDestroy = true;
        mQueue.clear();
        notEmpty->notifyAll();
        notFull->notifyAll();
    }

    inline void clear() {
        AutoLock l(mMutex);
        mQueue.clear();
        notEmpty->notifyAll();
    }

private:
    std::vector<T> mQueue;
    int mCapacity;

    Mutex mMutex;
    Condition notEmpty;
    Condition notFull;
    bool isDestroy;

    static const int DefaultCapacity = 1024;
};

}
#endif