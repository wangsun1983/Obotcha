#ifndef __OBOTCHA_CONCURRENT_QUEUE_HPP__
#define __OBOTCHA_CONCURRENT_QUEUE_HPP__

#include "Object.hpp"
#include "ArrayList.hpp"
#include "AutoLock.hpp"
#include "ContainerValue.hpp"
#include "ReadWriteLock.hpp"

namespace obotcha {

DECLARE_TEMPLATE_CLASS(ConcurrentQueue, T) {
  public:
    inline _ConcurrentQueue() {
        rdwrLock = createReadWriteLock();
        rdLock = rdwrLock->getReadLock();
        wrLock = rdwrLock->getWriteLock();
        mQueue = createArrayList<T>();
    }

    inline int size() {
        AutoLock l(rdLock);
        return mQueue->size();
    }

    // interface like ArrayList
    inline void add(T value) {
        putLast(value);
    }

    inline T get(int index) {
        AutoLock l(rdLock);
        return mQueue->get(index);
    }

    ArrayList<T> toArray() {
        AutoLock l(rdLock);
        ArrayList<T> list = createArrayList<T>();
        auto iterator = mQueue->getIterator();
        while(iterator->hasValue()) {
            list->add(iterator->getValue());
            iterator->next();
        }

        return list;
    }

    // interface like queue
    inline void putFirst(const T &val) {
        AutoLock l(wrLock);
        mQueue->insertFirst(val);
    }

    inline void putLast(const T &val) {
        AutoLock l(wrLock);
        mQueue->add(val);
    }

    inline int remove(const T &val) {
        AutoLock l(wrLock);
        return mQueue->remove(val);
    }

    inline T removeAt(int index) {
        AutoLock l(wrLock);
        return mQueue->removeAt(index);
    }

    inline T takeFirst() {
        AutoLock l(wrLock);
        return mQueue->removeAt(0);
    }

    inline T takeLast() {
        AutoLock l(wrLock);
        return mQueue->removeAt(mQueue->size() - 1);
    }

    inline ListIterator<T> getIterator() {
        return mQueue->getIterator();
    }

    inline void clear() {
        AutoLock l(wrLock);
        mQueue->clear();
    }

    void syncReadAction(std::function<void()> action) {
        AutoLock l(rdLock);
        action();
    }

    void syncWriteAction(std::function<void()> action) {
        AutoLock l(wrLock);
        action();
    }

    int removeAll(ArrayList<T> list) {
        AutoLock l(wrLock);
        return mQueue->removeAll(list);
    }

    Lock acquireReadLock() {
        return rdLock;
    }

  private:
    ArrayList<T> mQueue;

    ReadWriteLock rdwrLock;
    ReadLock rdLock;
    WriteLock wrLock;
};

} // namespace obotcha
#endif
