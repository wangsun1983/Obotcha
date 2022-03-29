#ifndef __OBOTCHA_THREAD_LOCAL_HPP__
#define __OBOTCHA_THREAD_LOCAL_HPP__

#include <pthread.h>
#include <vector>

#include "AutoLock.hpp"
#include "HashMap.hpp"
#include "Mutex.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ReadWriteLock.hpp"

namespace obotcha {

DECLARE_TEMPLATE_CLASS(ThreadLocal, 1) {
public:
    _ThreadLocal();

    void set(T t);

    void set(pthread_t, T t);

    T get();

    T get(pthread_t);

    void remove();

    void remove(pthread_t);

    int size();

    void clear();

    ~_ThreadLocal();

private:
    //Mutex mutex;
    ReadWriteLock rwLock;
    ReadLock rLock;
    WriteLock wLock;

    HashMap<pthread_t, T> mLocalMap;
};

template <typename T> _ThreadLocal<T>::_ThreadLocal() {
    mLocalMap = createHashMap<pthread_t, T>();
    //mutex = createMutex("ThreadLocalMutex");
    rwLock = createReadWriteLock();
    rLock = rwLock->getReadLock();
    wLock = rwLock->getWriteLock();
}

template <typename T> void _ThreadLocal<T>::set(pthread_t pthread, T t) {
    AutoLock l(wLock);
    mLocalMap->put(pthread, t);
}

template <typename T> void _ThreadLocal<T>::set(T t) {
    AutoLock l(wLock);
    mLocalMap->put(pthread_self(), t);
}

template <typename T> void _ThreadLocal<T>::remove(pthread_t ptread) {
    AutoLock l(wLock);
    mLocalMap->remove(ptread);
}

template <typename T> void _ThreadLocal<T>::remove() {
    AutoLock l(wLock);
    mLocalMap->remove(pthread_self());
}

template <typename T> T _ThreadLocal<T>::get() {
    AutoLock l(rLock);
    return mLocalMap->get(pthread_self());
}

template <typename T> T _ThreadLocal<T>::get(pthread_t t) {
    AutoLock l(rLock);
    return mLocalMap->get(t);
}

template <typename T> int _ThreadLocal<T>::size() {
    AutoLock l(rLock);
    return mLocalMap->size();
}

template <typename T> _ThreadLocal<T>::~_ThreadLocal() {
    AutoLock l(wLock);
    mLocalMap->clear();
}

template <typename T> void _ThreadLocal<T>::clear() {
    AutoLock l(wLock);
    mLocalMap->clear();
}

} // namespace obotcha
#endif