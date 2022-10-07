#ifndef __OBOTCHA_FOR_EVERY_ONE_HPP__
#define __OBOTCHA_FOR_EVERY_ONE_HPP__

#include "FileDescriptor.hpp"
#include "Lock.hpp"
#include "InputStream.hpp"
#include "Object.hpp"
#include "OutputStream.hpp"
#include "StrongPointer.hpp"
#include "ConcurrentHashMap.hpp"
#include "ConcurrentHashSet.hpp"
#include "ConcurrentLinkedList.hpp"
#include "ConcurrentQueue.hpp"
#include "BlockingLinkedList.hpp"

namespace obotcha {

template<typename T> 
Lock __forEveryOneAcquireLock(T list) {
    return nullptr;
}

template<typename U> 
Lock __forEveryOneAcquireLock(ConcurrentQueue<U> list) {
    return list->acquireReadLock();
}

template<typename U,typename V> 
Lock __forEveryOneAcquireLock(sp<_ConcurrentHashMap<U,V>> list) {
    return list->acquireReadLock();
}

template<typename U> 
Lock __forEveryOneAcquireLock(sp<_ConcurrentHashSet<U>> list) {
    return list->acquireReadLock();
}

template<typename U> 
Lock __forEveryOneAcquireLock(sp<_ConcurrentLinkedList<U>> list) {
    return list->acquireReadLock();
}

template<typename U> 
Lock __forEveryOneAcquireLock(sp<_BlockingLinkedList<U>> list) {
    return list->acquireReadLock();
}

#define ForEveryOne(X,Y) \
    auto X##__m_lock = __forEveryOneAcquireLock(Y);\
    AutoLock X##__forEveryOne_l(X##__m_lock);\
    auto X##__iterator = Y->getIterator();\
    for(auto X = X##__iterator->getItem();\
    X##__iterator->hasValue();\
    X##__iterator->next(),X##__iterator->hasValue()?X = X##__iterator->getItem():X=X)

} // namespace obotcha

#endif
