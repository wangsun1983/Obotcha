#ifndef __OBOTCHA_CONCURRENT_QUEUE_HPP__
#define __OBOTCHA_CONCURRENT_QUEUE_HPP__

#include <vector>

#include "ArrayList.hpp"
#include "AutoLock.hpp"
#include "ContainerValue.hpp"
#include "Mutex.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ReadWriteLock.hpp"

namespace obotcha {

DECLARE_TEMPLATE_CLASS(ConcurrentQueue, 1) {
  public:
    inline _ConcurrentQueue() {
        rdwrLock = createReadWriteLock();
        rdLock = rdwrLock->getReadLock();
        wrLock = rdwrLock->getWriteLock();
    }

    inline int size() {
        AutoLock l(rdLock);
        return mQueue.size();
    }

    // interface like ArrayList
    inline void add(T value) { 
        putLast(value); 
    }

    inline T get(int index) {
        AutoLock l(rdLock);
        if (index >= mQueue.size()) {
            return ContainerValue<T>(nullptr).get();
        }

        return mQueue.at(index);
    }

    ArrayList<T> toArray() {
        AutoLock l(rdLock);
        ArrayList<T> list = createArrayList<T>();
        for (T v : mQueue) {
            list->add(v);
        }

        return list;
    }

    // interface like queue
    inline void putFirst(const T &val) {
        AutoLock l(wrLock);
        mQueue.insert(mQueue.begin(), val);
    }

    inline void putLast(const T &val) {
        AutoLock l(wrLock);
        mQueue.push_back(val);
    }

    inline int remove(const T &val) {
        AutoLock l(wrLock);
        typename std::vector<T>::iterator result =
            find(mQueue.begin(), mQueue.end(), val);
        if (result != mQueue.end()) {
            mQueue.erase(result);
            return result - mQueue.begin();
        }

        return -1;
    }

    inline T removeAt(int index) {
        AutoLock l(wrLock);
        if (index < 0 || index >= mQueue.size() || mQueue.size() == 0) {
            Trigger(ArrayIndexOutOfBoundsException, "incorrect index");
        }

        T value = mQueue.at(index);
        mQueue.erase(mQueue.begin() + index);
        return value;
    }

    inline T takeFirst() {
        AutoLock l(wrLock);

        if (mQueue.size() == 0) {
            return ContainerValue<T>(nullptr).get();
        }

        T ret = mQueue.at(0);
        mQueue.erase(mQueue.begin());

        return ret;
    }

    inline T takeLast() {
        AutoLock l(wrLock);

        if (mQueue.size() == 0) {
            return ContainerValue<T>(nullptr).get();
        }

        // return mQueue.pop_back();
        T ret = mQueue.back();
        mQueue.pop_back();

        return ret;
    }

    inline void clear() {
        AutoLock l(wrLock);
        mQueue.clear();
    }

  private:
    std::vector<T> mQueue;

    ReadWriteLock rdwrLock;
    ReadLock rdLock;
    WriteLock wrLock;
};

} // namespace obotcha
#endif