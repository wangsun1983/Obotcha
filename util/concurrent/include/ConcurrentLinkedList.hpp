#ifndef __OBOTCHA_CONCURRENT_LINKEDLIST_HPP__
#define __OBOTCHA_CONCURRENT_LINKEDLIST_HPP__

#include <vector>

#include "LinkedList.hpp"
#include "AutoLock.hpp"
#include "ContainerValue.hpp"
#include "Mutex.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ReadWriteLock.hpp"
#include "System.hpp"

namespace obotcha {

DECLARE_TEMPLATE_CLASS(ConcurrentLinkedList, T) {
  public:
    inline _ConcurrentLinkedList() {
        rdwrLock = createReadWriteLock();
        rdLock = rdwrLock->getReadLock();
        wrLock = rdwrLock->getWriteLock();
        mQueue = createLinkedList<T>();
    }

    inline int size() {
        AutoLock l(rdLock);
        return mQueue->size();
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
        mQueue->putFirst(val);
    }

    inline void putLast(const T &val) {
        AutoLock l(wrLock);
        //mQueue.push_back(val);
        mQueue->putLast(val);
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
        return mQueue->takeFirst();
    }

    inline T takeLast() {
        AutoLock l(wrLock);
        return mQueue->taskLast();
    }

    inline ListIterator<T> getIterator() {
        AutoLock l(rdLock);
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

/*
    void foreach(std::function<int(const T &)> f,std::function<void()> after = nullptr) {
        auto lock = ((after == nullptr)?Cast<Lock>(rdLock):Cast<Lock>(wrLock));
        AutoLock l(lock);

        auto iterator = mQueue->getIterator();
        while(iterator->hasValue()) {
            if(f(iterator->getValue()) != Continue) {
                break;
            }
            iterator->next();
        }
        if(after != nullptr) {
            after();
            return;
        }
    }
*/
    Lock acquireReadLock() {
        return rdLock;
    }

  private:
    LinkedList<T> mQueue;

    ReadWriteLock rdwrLock;
    ReadLock rdLock;
    WriteLock wrLock;
};

} // namespace obotcha
#endif
