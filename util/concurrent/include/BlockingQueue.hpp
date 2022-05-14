#ifndef __OBOTCHA_BLOCKING_QUEUE_HPP__
#define __OBOTCHA_BLOCKING_QUEUE_HPP__

#include <errno.h>
#include <unistd.h>
#include <vector>

#include "ArrayList.hpp"
#include "AutoLock.hpp"
#include "Condition.hpp"
#include "ContainerValue.hpp"
#include "Error.hpp"
#include "InitializeException.hpp"
#include "Mutex.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

#define BLOCK_QUEUE_ADD_NOLOCK(Action)                                         \
    if (!isDestroy) {                                                          \
        int size = mQueue.size();                                              \
        if (mCapacity > 0 && size == mCapacity) {                              \
            return false;                                                      \
        }                                                                      \
        Action;                                                                \
        notEmpty->notify();                                                    \
        return true;                                                           \
    }                                                                          \
    return false;

#define BLOCK_QUEUE_ADD(Action)                                                \
    AutoLock l(mMutex);                                                        \
    while (!isDestroy) {                                                       \
        int size = mQueue.size();                                              \
        if (mCapacity > 0 && size == mCapacity) {                              \
            if (-ETIMEDOUT == notFull->wait(mMutex, timeout)) {              \
                return false;                                                  \
            }                                                                  \
            continue;                                                          \
        }                                                                      \
        Action;                                                                \
        notEmpty->notify();                                                    \
        return true;                                                           \
    }                                                                          \
    return false;

#define BLOCK_QUEUE_REMOVE(Action)                                             \
    T ret;                                                                     \
    AutoLock l(mMutex);                                                        \
    while (!isDestroy) {                                                       \
        int size = mQueue.size();                                              \
        if (size == 0) {                                                       \
            if (-ETIMEDOUT == notEmpty->wait(mMutex, timeout)) {             \
                return ContainerValue<T>(nullptr).get();                       \
            }                                                                  \
            continue;                                                          \
        }                                                                      \
        Action if (mCapacity > 0) { notFull->notify(); }                       \
        return ret;                                                            \
    }                                                                          \
    return ContainerValue<T>(nullptr).get();

#define BLOCK_QUEUE_REMOVE_NOBLOCK(Action)                                     \
    T ret;                                                                     \
    AutoLock l(mMutex);                                                        \
    if (!isDestroy) {                                                          \
        int size = mQueue.size();                                              \
        if (size == 0) {                                                       \
            return ContainerValue<T>(nullptr).get();                           \
        }                                                                      \
        Action if (mCapacity > 0) { notFull->notify(); }                       \
        return ret;                                                            \
    }                                                                          \
    return ContainerValue<T>(nullptr).get();

DECLARE_TEMPLATE_CLASS(BlockingQueue, T) {
  public:
    _BlockingQueue(int size) : mCapacity(size) {
        mMutex = createMutex("BlockingQueueMutex");
        notEmpty = createCondition();
        notFull = createCondition();
        isDestroy = false;
        mCapacity = size;
    }

    _BlockingQueue() : _BlockingQueue(-1) {}

    ~_BlockingQueue() {}

    inline int size() {
        AutoLock l(mMutex);
        return mQueue.size();
    }

    inline int capacity() { return mCapacity; }

    inline void freeze() { mMutex->lock(); }

    inline void unfreeze() { mMutex->unlock(); }

    /**
     * Retrieves and removes the head of the queue represented by this deque
     * (in other words, the first element of this deque), waiting if
     * necessary until an element becomes available.
     */
    inline bool putFirst(const T &val, long timeout = 0) {
        BLOCK_QUEUE_ADD(mQueue.insert(mQueue.begin(), val));
    }

    inline bool putLast(const T &val, long timeout = 0) {
        BLOCK_QUEUE_ADD(mQueue.emplace_back(val));
    }

    inline bool tryPutFirst(const T &val) {
        BLOCK_QUEUE_ADD_NOLOCK(mQueue.insert(mQueue.begin(), val));
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
        return (mQueue.size() == 0) ? nullptr : mQueue[0];
    }

    inline T peekLast() {
        AutoLock l(mMutex);
        return (mQueue.size() == 0) ? nullptr : mQueue[mQueue.size() - 1];
    }

    // add some interface like ArrayList
    inline T removeAt(int index) {
        AutoLock l(mMutex);
        if (index < 0 || index >= mQueue.size() || mQueue.size() == 0) {
            Trigger(ArrayIndexOutOfBoundsException, "incorrect index");
        }

        T val = mQueue.at(index);
        mQueue.erase(mQueue.begin() + index);
        return val;
    }

    inline int remove(const T &val) {
        typename std::vector<T>::iterator result =
            find(mQueue.begin(), mQueue.end(), val);
        if (result != mQueue.end()) {
            mQueue.erase(result);
            return result - mQueue.begin();
        }

        return -1;
    }

    // add some simple function
    inline bool put(T v) {
        return putLast(v);
    }

    inline T take() {
        return takeFirst();
    }

    inline T peek() {
        return peekLast();
    }

    inline ArrayList<T> toArray() {
        AutoLock l(mMutex);
        ArrayList<T> array = createArrayList<T>();
        for (T value : mQueue) {
            array->add(value);
        }
        return array;
    }

    // add foreach lambda
    inline void foreach (std::function<int(const T &)> callback,
                         std::function<void()> after = nullptr) {
        AutoLock l(mMutex);
        for (T value : mQueue) {
            if (callback(value) == Global::Break) {
                break;
            }
        }

        if(after != nullptr) {
          after();
        }
    }

    //
    // destroy
    inline void destroy() {
        AutoLock l(mMutex);
        isDestroy = true;
        mQueue.clear();
        notEmpty->notifyAll();
        if (mCapacity > 0) {
            notFull->notify();
        }
    }

    inline void clear() {
        AutoLock l(mMutex);
        mQueue.clear();

        if (mCapacity > 0) {
            notFull->notifyAll();
        }
    }

  private:
    std::vector<T> mQueue;
    int mCapacity;

    Mutex mMutex;
    Condition notEmpty;
    Condition notFull;
    bool isDestroy;
};

} // namespace obotcha
#endif
