#ifndef __OBOTCHA_BLOCKING_LINKED_LIST_HPP__
#define __OBOTCHA_BLOCKING_LINKED_LIST_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "AutoLock.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "LinkedList.hpp"
#include "Error.hpp"

namespace obotcha {

#define LINKED_LIST_ADD(Action) \
AutoLock l(mMutex);\
while(!isDestroy) {\
    if(mCapacity != -1 && mList->size() == mCapacity) {\
        if(mEnqueueCond->wait(mMutex,timeout) == -WaitTimeout) {\
            return false;\
        }\
        continue;\
    }\
    Action;\
    mDequeueCond->notify();\
    break;\
}\
return true;\

#define LINKED_LIST_REMOVE(Action) \
T data;\
AutoLock l(mMutex);\
while(!isDestroy) {\
    if(mList->size() == 0) {\
        if(mDequeueCond->wait(mMutex,timeout) == -WaitTimeout) {\
            return nullptr;\
        }\
        continue;\
    }\
    Action;\
    mEnqueueCond->notify();\
    return data;\
}\
return nullptr;\

#define LINKED_LIST_REMOVE_NOBLOCK(Action) \
T data;\
AutoLock l(mMutex);\
while(!isDestroy) {\
    if(mList->size() == 0) {\
        return nullptr;\
    }\
    Action;\
    mEnqueueCond->notify();\
    return data;\
}\
return nullptr;\


DECLARE_CLASS(BlockingLinkedList,1) {
public:
    _BlockingLinkedList(int capacity = -1) {
        mMutex = createMutex("BlockingLinkedList");
        mList = createLinkedList<T>();
        mCapacity = capacity;
        mEnqueueCond = createCondition();
        mDequeueCond = createCondition();
        isDestroy = false;
    }

    bool isEmpty() {
        AutoLock l(mMutex);
        return mList->isEmpty();
    }

    int size() {
        AutoLock l(mMutex);
        return mList->size();
    }

    inline void enQueueFirst(T val) {
        enQueueFirst(val,0);
    }

    inline void enQueueLast(T val) {
        enQueueLast(val,0);
    }

    inline bool enQueueFirst(T val,long timeout) {
        LINKED_LIST_ADD(mList->enQueueFirst(val));
    }

    inline bool enQueueLast(T val,long timeout) {
        LINKED_LIST_ADD(mList->enQueueLast(val));
    }

    inline T deQueueFirst() {
        return deQueueFirst(0);
    }

    inline T deQueueLast() {
        return deQueueLast(0);
    }

    inline T deQueueFirst(long timeout) {
        LINKED_LIST_REMOVE(data = mList->deQueueFirst());
    }

    inline T deQueueLast(long timeout) {
        LINKED_LIST_REMOVE(data = mList->deQueueLast());
    }

    inline T deQueueFirstNoBlock() {
        LINKED_LIST_REMOVE_NOBLOCK(data = mList->deQueueFisrt());
    }

    inline T deQueueLastNoBlock() {
        LINKED_LIST_REMOVE_NOBLOCK(data = mList->deQueueLast());
    }

    //destroy
    inline void destroy() {
        AutoLock l(mMutex);
        mList->clear();
        isDestroy = true;
    }

    inline void clear() {
        AutoLock l(mMutex);
        mList->clear();
    }

private:
    LinkedList<T> mList;
    int mCapacity;
    Mutex mMutex;
    Condition mEnqueueCond;
    Condition mDequeueCond;
    bool isDestroy;
};

}
#endif