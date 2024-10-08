#ifndef __OBOTCHA_CONCURRENT_LINKEDLIST_HPP__
#define __OBOTCHA_CONCURRENT_LINKEDLIST_HPP__


#include "Object.hpp"
#include "LinkedList.hpp"
#include "AutoLock.hpp"
#include "ReadWriteLock.hpp"

namespace obotcha {

DECLARE_TEMPLATE_CLASS(ConcurrentLinkedList, T) {
  public:
    inline _ConcurrentLinkedList() {
        rdLock = rdwrLock->getReadLock();
        wrLock = rdwrLock->getWriteLock();
    }

    inline int size() {
        AutoLock l(rdLock);
        return mQueue->size();
    }

    ArrayList<T> toArray() {
        AutoLock l(rdLock);
        ArrayList<T> list = ArrayList<T>::New();
        auto iterator = mQueue->getIterator();
        while(iterator->hasValue()) {
            list->add(iterator->getValue());
            iterator->next();
        }

        return list;
    }

    inline T peekFirst() {
        AutoLock l(rdLock);
        return mQueue->peekFirst();
    }

    inline T peekLast() {
        AutoLock l(rdLock);
        return mQueue->peekLast();
    }

    // interface like queue
    inline void putFirst(const T &val) {
        AutoLock l(wrLock);
        mQueue->putFirst(val);
    }

    inline void putLast(const T &val) {
        AutoLock l(wrLock);
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

    inline LinkedListIterator<T> getIterator() {
        return mQueue->getIterator();
    }

    inline void clear() {
        AutoLock l(wrLock);
        mQueue->clear();
    }

    template<class Function>
    void syncReadAction(Function action) {
        AutoLock l(rdLock);
        action();
    }

    template<class Function>
    void syncWriteAction(Function action) {
        AutoLock l(wrLock);
        action();
    }

    Lock acquireReadLock() {
        return rdLock;
    }

  private:
    LinkedList<T> mQueue = LinkedList<T>::New();
    ReadWriteLock rdwrLock = ReadWriteLock::New();
    ReadLock rdLock;
    WriteLock wrLock;
};

} // namespace obotcha
#endif
