#ifndef __OBOTCHA_BLOCKING_LINKED_LIST_HPP__
#define __OBOTCHA_BLOCKING_LINKED_LIST_HPP__

#include "Object.hpp"
#include "ArrayList.hpp"
#include "AutoLock.hpp"
#include "Condition.hpp"
#include "ContainerValue.hpp"
#include "Error.hpp"
#include "LinkedList.hpp"
#include "Mutex.hpp"

namespace obotcha {

#define LINKED_LIST_ADD(Action)                                                \
    AutoLock l(mMutex);                                                        \
    if(notFull->wait(mMutex,timeout,[this]{                                    \
          return mIsDestroy ||mCapacity == kLinkedListSizeInfinite             \
                || mList->size() != mCapacity;})                               \
          == -ETIMEDOUT) {                                                     \
        return false;                                                          \
    }                                                                          \
    Inspect(mIsDestroy,false)                                                  \
    Action;                                                                    \
    if(notEmpty->getWaitCount() != 0){ notEmpty->notify(); }                   \
    return true;                                                           

#define LINKED_LIST_ADD_NOBLOCK(Action)                                        \
    AutoLock l(mMutex);                                                        \
    Inspect(mIsDestroy||(mCapacity != kLinkedListSizeInfinite                  \
         && mList->size() == mCapacity),false)                                 \
    Action;                                                                    \
    if(notEmpty->getWaitCount() != 0){ notEmpty->notify(); }                   \
    return true;

#define LINKED_LIST_REMOVE(Action)                                             \
    T data;                                                                    \
    AutoLock l(mMutex);                                                        \
    if(notEmpty->wait(mMutex, timeout,[this]{                                  \
        return mIsDestroy || mList->size() != 0;}) == -ETIMEDOUT) {            \
        return ContainerValue<T>(nullptr).get();                               \
    }                                                                          \
    Inspect(mIsDestroy,ContainerValue<T>(nullptr).get())                       \
    Action;                                                                    \
    if (notFull->getWaitCount() != 0) { notFull->notify(); }                   \
    return data;                                                           

#define LINKED_LIST_REMOVE_NOBLOCK(Action)                                     \
    T data;                                                                    \
    AutoLock l(mMutex);                                                        \
    if (mIsDestroy || mList->size() == 0) {                                    \
        return ContainerValue<T>(nullptr).get();                               \
    }                                                                          \
    Action;                                                                    \
    if (notFull->getWaitCount() != 0) { notFull->notify(); }                   \
    return data;

DECLARE_TEMPLATE_CLASS(BlockingLinkedList, T) {
  public:
    static const int kLinkedListSizeInfinite = -1;

    explicit _BlockingLinkedList(int capacity = kLinkedListSizeInfinite) {
        mMutex = createMutex("BlockingLinkedList");
        mList = createLinkedList<T>();
        mCapacity = capacity;
        notEmpty = createCondition();
        notFull = createCondition();
        mIsDestroy = false;
    }

    inline int size() {
        AutoLock l(mMutex);
        return mList->size();
    }

    inline int capacity() {
        return mCapacity;
    }

    inline bool putFirst(const T &val, long timeout = 0) {
        LINKED_LIST_ADD(mList->putFirst(val));
    }

    inline bool putLast(const T &val, long timeout = 0) {
        LINKED_LIST_ADD(mList->putLast(val));
    }

    inline bool tryPutFirst(const T &val) {
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
        LINKED_LIST_REMOVE_NOBLOCK(data = mList->takeFirst());
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

    inline bool put(T v) { 
        return putLast(v); 
    }

    inline T take(long timeout = 0) { 
        return takeFirst(timeout); 
    }

    inline T peek() { 
        return peekFirst(); 
    }

    inline T removeAt(int index) {
        AutoLock l(mMutex);
        Panic(index < 0 || index >= mList->size() || mList->size() == 0,
                ArrayIndexOutOfBoundsException, "incorrect index");

        T value = mList->removeAt(index);
        if(notFull->getWaitCount() != 0) { notFull->notify(); }
        return value;
    }

    inline int remove(T value) {
        AutoLock l(mMutex);
        int index = mList->remove(value);
        if(notFull->getWaitCount() != 0 && index != -1) { notFull->notify(); }
        return index;
    }

    Lock acquireReadLock() {
        return mMutex;
    }

    ArrayList<T> toArray() {
        AutoLock l(mMutex);
        ArrayList<T> list = createArrayList<T>();
        auto iterator = mList->getIterator();
        while(iterator->hasValue()) {
            list->add(iterator->getValue());
            iterator->next();
        }
        return list;
    }

    // destroy
    inline void destroy() {
        AutoLock l(mMutex);
        mIsDestroy = true;
        clear();
        if(notEmpty->getWaitCount() != 0) { notEmpty->notifyAll(); }
    }

    inline void clear() {
        AutoLock l(mMutex);
        mList->clear();
        if(notFull->getWaitCount() != 0) { notFull->notifyAll(); }
    }

    LinkedListIterator<T> getIterator() {
        AutoLock l(mMutex);
        return mList->getIterator();
    }

  private:
    LinkedList<T> mList;
    // if mCapacity < 0,it means the queue is infinite
    int mCapacity; 
    Mutex mMutex;
    Condition notEmpty;
    Condition notFull;
    bool mIsDestroy;
};



} // namespace obotcha
#endif
