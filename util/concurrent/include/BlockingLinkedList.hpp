#ifndef __OBOTCHA_BLOCKING_LINKED_LIST_HPP__
#define __OBOTCHA_BLOCKING_LINKED_LIST_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "AutoLock.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "LinkedList.hpp"
#include "Error.hpp"
#include "ContainerValue.hpp"

namespace obotcha {

#define LINKED_LIST_ADD(Action) \
AutoLock l(mMutex);\
while(!isDestroy) {\
    if(mCapacity != -1 && mList->size() == mCapacity) {\
        if(notFull->wait(mMutex,timeout) == -WaitTimeout) {\
            return false;\
        }\
        continue;\
    }\
    Action;\
    notEmpty->notify();\
    break;\
}\
return true;\

#define LINKED_LIST_ADD_NOBLOCK(Action) \
AutoLock l(mMutex);\
if(!isDestroy) { \
    if(mCapacity != -1 && mList->size() == mCapacity) {\
        return false;\
    }\
    Action;\
    notEmpty->notify();\
}\
return true;\

#define LINKED_LIST_REMOVE(Action) \
T data;\
AutoLock l(mMutex);\
while(!isDestroy) {\
    if(mList->size() == 0) {\
        if(notEmpty->wait(mMutex,timeout) == -WaitTimeout) {\
            return ContainerValue<T>(nullptr).get();\
        }\
        continue;\
    }\
    Action;\
    notFull->notify();\
    return data;\
}\
return nullptr;\

#define LINKED_LIST_REMOVE_NOBLOCK(Action) \
T data;\
AutoLock l(mMutex);\
while(!isDestroy) {\
    if(mList->size() == 0) {\
        return ContainerValue<T>(nullptr).get();\
    }\
    Action;\
    notFull->notify();\
    return data;\
}\
return nullptr;\


DECLARE_CLASS(BlockingLinkedList,1) {
public:
    _BlockingLinkedList(int capacity = -1) {
        mMutex = createMutex("BlockingLinkedList");
        mList = createLinkedList<T>();
        mCapacity = capacity;
        notEmpty = createCondition();
        notFull = createCondition();
        isDestroy = false;
    }

    inline int size() {
        AutoLock l(mMutex);
        return mList->size();
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

    inline bool putFirst(const T & val,long timeout = 0) {
        LINKED_LIST_ADD(mList->putFirst(val));
    }

    inline bool putLast(const T &val,long timeout = 0) {
        LINKED_LIST_ADD(mList->putLast(val));
    }

    inline bool tryPutFirst(const T & val) {
        LINKED_LIST_ADD_NOBLOCK(mList->putFirst(val));
    }

    inline bool tryPutLast(const T &val) {
        LINKED_LIST_ADD_NOBLOCK(mList->putLast(val));
    }

    inline T takeFirst(long timeout = 0) {
        LINKED_LIST_REMOVE(data = mList->takeFirst());
    }

    inline T takeLast(long timeout = 0) {
        LINKED_LIST_REMOVE(data = mList->takeLast());
    }

    inline T tryTakeFirst() {
        LINKED_LIST_REMOVE_NOBLOCK(data = mList->deQueueFisrt());
    }

    inline T tryTakeLast() {
        LINKED_LIST_REMOVE_NOBLOCK(data = mList->takeLast());
    }

    inline T peekFirst() {
        AutoLock l(mMutex);
        return mList->first();
    }

    inline T peekLast() {
        AutoLock l(mMutex);
        return mList->last();
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
        notFull->notifyAll();
    }

private:
    LinkedList<T> mList;
    int mCapacity;
    Mutex mMutex;
    Condition notEmpty;
    Condition notFull;
    bool isDestroy;
};

}
#endif