#ifndef __OBOTCHA_BLOCKING_LINKED_LIST_HPP__
#define __OBOTCHA_BLOCKING_LINKED_LIST_HPP__

#include "ArrayList.hpp"
#include "AutoLock.hpp"
#include "Condition.hpp"
#include "ContainerValue.hpp"
#include "Error.hpp"
#include "LinkedList.hpp"
#include "Mutex.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

#define LINKED_LIST_ADD(Action)                                                \
    AutoLock l(mMutex);                                                        \
    while (!isDestroy) {                                                       \
        if (mCapacity != -1 && mList->size() == mCapacity) {                   \
            if (notFull->wait(mMutex, timeout) == -ETIMEDOUT) {              \
                return false;                                                  \
            }                                                                  \
            continue;                                                          \
        }                                                                      \
        Action;                                                                \
        notEmpty->notify();                                                    \
        break;                                                                 \
    }                                                                          \
    return false;

#define LINKED_LIST_ADD_NOBLOCK(Action)                                        \
    AutoLock l(mMutex);                                                        \
    if (!isDestroy) {                                                          \
        if (mCapacity != -1 && mList->size() == mCapacity) {                   \
            return false;                                                      \
        }                                                                      \
        Action;                                                                \
        notEmpty->notify();                                                    \
    }                                                                          \
    return false;

#define LINKED_LIST_REMOVE(Action)                                             \
    T data;                                                                    \
    AutoLock l(mMutex);                                                        \
    while (!isDestroy) {                                                       \
        if (mList->size() == 0) {                                              \
            if (notEmpty->wait(mMutex, timeout) == -ETIMEDOUT) {             \
                return ContainerValue<T>(nullptr).get();                       \
            }                                                                  \
            continue;                                                          \
        }                                                                      \
        Action;                                                                \
        notFull->notify();                                                     \
        return data;                                                           \
    }                                                                          \
    return ContainerValue<T>(nullptr).get();

#define LINKED_LIST_REMOVE_NOBLOCK(Action)                                     \
    T data;                                                                    \
    AutoLock l(mMutex);                                                        \
    while (!isDestroy) {                                                       \
        if (mList->size() == 0) {                                              \
            return ContainerValue<T>(nullptr).get();                           \
        }                                                                      \
        Action;                                                                \
        notFull->notify();                                                     \
        return data;                                                           \
    }                                                                          \
    return ContainerValue<T>(nullptr).get();

DECLARE_TEMPLATE_CLASS(BlockingLinkedList, T) {
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

    //inline void freeze() {
    //    mMutex->lock();
    //}

    //inline void unfreeze() {
    //    mMutex->unlock();
    //}

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

    // add some simple function
    inline bool put(T v) { return putLast(v); }

    inline T take() { return takeFirst(); }

    inline T peek() { return peekLast(); }

    inline T removeAt(int index) {
        AutoLock l(mMutex);
        if (index < 0 || index >= mList->size() || mList->size() == 0) {
            Trigger(ArrayIndexOutOfBoundsException, "incorrect index");
        }

        T value = mList->removeAt(index);
        if (mCapacity > 0) {
            notFull->notify();
        }
        return value;
    }

    inline int remove(T value) {
        AutoLock l(mMutex);
        int index = mList->remove(value);
        if (mCapacity > 0) {
            notFull->notify();
        }
        return index;
    }

    inline void foreach (std::function<int(const T&)> callback,std::function<void()> after = nullptr) {
        AutoLock l(mMutex);
        mList->foreach ([&callback](T v) { return callback(v); });
        if(after != nullptr) {
          after();
        }
    }

    ArrayList<T> toArray() {
        AutoLock l(mMutex);
        ArrayList<T> list = createArrayList<T>();
        mList->foreach ([&list](T value) {
            list->add(value);
            return Global::Continue;
        });
        return list;
    }

    // destroy
    inline void destroy() {
        AutoLock l(mMutex);
        mList->clear();
        isDestroy = true;
        notEmpty->notifyAll();
        if (mCapacity > 0) {
            notFull->notify();
        }
    }

    inline void clear() {
        AutoLock l(mMutex);
        mList->clear();
        notFull->notifyAll();
    }

    LinkedListIterator<T> getIterator() {
        AutoLock l(mMutex);
        return mList->getIterator();
    }

  private:
    LinkedList<T> mList;
    int mCapacity;
    Mutex mMutex;
    Condition notEmpty;
    Condition notFull;
    bool isDestroy;
};

} // namespace obotcha
#endif
