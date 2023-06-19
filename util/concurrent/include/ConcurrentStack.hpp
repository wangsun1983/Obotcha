#ifndef __OBOTCHA_CONCURRENT_STACK_HPP__
#define __OBOTCHA_CONCURRENT_STACK_HPP__


#include "Object.hpp"
#include "Stack.hpp"
#include "AutoLock.hpp"
#include "ContainerValue.hpp"
#include "ReadWriteLock.hpp"

namespace obotcha {

DECLARE_TEMPLATE_CLASS(ConcurrentStack, T) {
  public:
    inline _ConcurrentStack() {
        rdwrLock = createReadWriteLock();
        rdLock = rdwrLock->getReadLock();
        wrLock = rdwrLock->getWriteLock();
        mStack = createStack<T>();
    }

    inline int size() {
        AutoLock l(rdLock);
        return mStack->size();
    }

    // interface like queue
    inline void push(const T &val) {
        AutoLock l(wrLock);
        mStack->push(val);
    }

    T pop() {
        AutoLock l(wrLock);
        return mStack->pop();
    }

    inline StackIterator<T> getIterator() {
        return mStack->getIterator();
    }

    inline void clear() {
        AutoLock l(wrLock);
        mStack->clear();
    }

    void syncReadAction(std::function<void()> action) {
        AutoLock l(rdLock);
        action();
    }

    void syncWriteAction(std::function<void()> action) {
        AutoLock l(wrLock);
        action();
    }

    Lock acquireReadLock() {
        return rdLock;
    }

  private:
    Stack<T> mStack;

    ReadWriteLock rdwrLock;
    ReadLock rdLock;
    WriteLock wrLock;
};

} // namespace obotcha
#endif
