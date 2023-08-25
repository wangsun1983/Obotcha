#ifndef __OBOTCHA_BLOCKING_QUEUE_HPP__
#define __OBOTCHA_BLOCKING_QUEUE_HPP__

#include <unistd.h>
#include <vector>

#include "Object.hpp"
#include "ArrayList.hpp"
#include "AutoLock.hpp"
#include "Condition.hpp"
#include "ContainerValue.hpp"
#include "Mutex.hpp"
#include "Definations.hpp"

namespace obotcha {

template <typename T> class _BlockingQueueIterator;

#define BLOCK_QUEUE_ADD_NOLOCK(Action)                                         \
    AutoLock l(mMutex);                                                        \
    Inspect(mIsDestroy||(mCapacity != kQueueSizeInfinite                      \
         && mQueue.size() == mCapacity),false)                                 \
    Action;                                                                    \
    if(notEmpty->getWaitCount() != 0){ notEmpty->notify(); }                   \
    return true;

#define BLOCK_QUEUE_ADD(Action)                                                \
    AutoLock l(mMutex);                                                        \
    if(notFull->wait(mMutex,timeout,[this]{                                    \
          return mIsDestroy ||mCapacity == kQueueSizeInfinite                 \
                || mQueue.size() != mCapacity;})                               \
          == -ETIMEDOUT) {                                                     \
        return false;                                                          \
    }                                                                          \
    Inspect(mIsDestroy,false)                                                  \
    Action;                                                                    \
    if(notEmpty->getWaitCount() != 0){ notEmpty->notify(); }                   \
    return true;        

#define BLOCK_QUEUE_REMOVE(Action)                                             \
    T data;                                                                    \
    AutoLock l(mMutex);                                                        \
    if(notEmpty->wait(mMutex, timeout,[this]{                                  \
        return mIsDestroy || mQueue.size() != 0;}) == -ETIMEDOUT) {            \
        return ContainerValue<T>(nullptr).get();                               \
    }                                                                          \
    Inspect(mIsDestroy,ContainerValue<T>(nullptr).get())                       \
    Action;                                                                    \
    if (notFull->getWaitCount() != 0) { notFull->notify(); }                   \
    return data;    

#define BLOCK_QUEUE_REMOVE_NOBLOCK(Action)                                     \
    T data;                                                                    \
    AutoLock l(mMutex);                                                        \
    if (mIsDestroy || mQueue.size() == 0) {                                    \
        return ContainerValue<T>(nullptr).get();                               \
    }                                                                          \
    Action;                                                                    \
    if (notFull->getWaitCount() != 0) { notFull->notify(); }                   \
    return data;

DECLARE_TEMPLATE_CLASS(BlockingQueue, T) {
  public:
    friend class _BlockingQueueIterator<T>;
    static const int kQueueSizeInfinite;
    explicit _BlockingQueue(int size = kQueueSizeInfinite) : mCapacity(size) {
        mMutex = createMutex("BlockingQueueMutex");
        notEmpty = createCondition();
        notFull = createCondition();
    }

    ~_BlockingQueue() override = default;

    inline int size() const {
        AutoLock l(mMutex);
        return mQueue.size();
    }

    inline int capacity() const { 
        return mCapacity; 
    }

    /**
     * Retrieves and removes the head of the queue represented by this deque
     * (in other words, the first element of this deque), waiting if
     * necessary until an element becomes available.
     */
    inline bool putFirst(const T &val, long timeout = 0) {
        BLOCK_QUEUE_ADD(mQueue.insert(mQueue.begin(), val))
    }

    inline bool putLast(const T &val, long timeout = 0) {
        BLOCK_QUEUE_ADD(mQueue.emplace_back(val))
    }

    inline bool tryPutFirst(const T &val) {
        BLOCK_QUEUE_ADD_NOLOCK(mQueue.insert(mQueue.begin(), val))
    }

    inline bool tryPutLast(const T &val) {
        BLOCK_QUEUE_ADD_NOLOCK(mQueue.emplace_back(val))
    }

    /**
     * Retrieves and removes the first element of this deque, waiting
     * if necessary until an element becomes available.
     */
    inline T takeFirst(long timeout = 0) {
        BLOCK_QUEUE_REMOVE({
            data = mQueue.at(0);
            mQueue.erase(mQueue.begin());
        })
    }

    inline T takeLast(long timeout = 0) {
        BLOCK_QUEUE_REMOVE({
            data = mQueue.back();
            mQueue.pop_back();
        })
    }

    inline T tryTakeFirst() {
        BLOCK_QUEUE_REMOVE_NOBLOCK({
            data = mQueue.at(0);
            mQueue.erase(mQueue.begin());
        })
    }

    inline T tryTakeLast() {
        BLOCK_QUEUE_REMOVE_NOBLOCK({
            data = mQueue.back();
            mQueue.pop_back();
        })
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
        Panic(index < 0 || index >= mQueue.size() || mQueue.size() == 0,
            ArrayIndexOutOfBoundsException, "incorrect index")
        
        T val = mQueue.at(index);
        mQueue.erase(mQueue.begin() + index);
        if(notFull->getWaitCount() != 0) { notFull->notify(); }
        return val;
    }

    inline int remove(const T &val) {
        typename std::vector<T>::iterator result = find(mQueue.begin(), mQueue.end(), val);
        if (result != mQueue.end()) {
            mQueue.erase(result);
            if(notFull->getWaitCount() != 0) { notFull->notify(); }
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
        return peekFirst();
    }

    inline ArrayList<T> toArray() {
        AutoLock l(mMutex);
        ArrayList<T> array = createArrayList<T>();
        for (T value : mQueue) {
            array->add(value);
        }
        return array;
    }

    sp<_BlockingQueueIterator<T>> getIterator() {
        return AutoClone(new _BlockingQueueIterator<T>(this));
    }

    Lock acquireReadLock() {
        return mMutex;
    }

    // add foreach lambda
    inline void foreach (std::function<int(const T &)> callback,
                         std::function<void()> after = nullptr) {
        AutoLock l(mMutex);
        for (T value : mQueue) {
            if (callback(value) == st(Defination)::Break) {
                break;
            }
        }

        if(after != nullptr) {
          after();
        }
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
        mQueue.clear();
        if(notFull->getWaitCount() != 0) { notFull->notifyAll(); }
    }

  private:
    std::vector<T> mQueue;
    int mCapacity;

    Mutex mMutex;
    Condition notEmpty;
    Condition notFull;
    bool mIsDestroy = false;
};

template<class T>
const int _BlockingQueue<T>::kQueueSizeInfinite = -1;

//----------------- ArrayListIterator ---------------------
DECLARE_TEMPLATE_CLASS(BlockingQueueIterator, T) {
public:
    explicit _BlockingQueueIterator(_BlockingQueue<T> * list):_BlockingQueueIterator(AutoClone(list)) {
    }

    explicit _BlockingQueueIterator(BlockingQueue<T> list):mList(list),
                                                           iterator(list->mQueue.begin()) {
    }

    T getValue() {
        Panic(iterator == mList->mQueue.end(),
            ArrayIndexOutOfBoundsException, "no data")
        return *iterator;
    }

    bool hasValue() {
        return iterator != mList->mQueue.end();
    }

    bool next() {
        if (iterator != mList->mQueue.end()) {
            iterator++;
        }

        return iterator != mList->mQueue.end();
    }

    T getItem() {
        return getValue();
    }

private:
    BlockingQueue<T> mList;
    typename std::vector<T>::iterator iterator;
};

} // namespace obotcha
#endif
