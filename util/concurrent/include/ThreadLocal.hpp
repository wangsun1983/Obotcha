#ifndef __OBOTCHA_THREAD_LOCAL_HPP__
#define __OBOTCHA_THREAD_LOCAL_HPP__

#include <vector>
#include <pthread.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "HashMap.hpp"
#include "Mutex.hpp"
#include "AutoLock.hpp"

namespace obotcha {

DECLARE_CLASS(ThreadLocal,1) {
public:
    _ThreadLocal();

    void set(T t);

    void set(pthread_t,T t);

    T get();

    T get(pthread_t);

    void remove();

    void remove(pthread_t);

    int size();

    void clear();

    ~_ThreadLocal();

private:

    Mutex mutex;

    HashMap<pthread_t,T> mLocalMap;
};

template<typename T>
_ThreadLocal<T>::_ThreadLocal(){
    mLocalMap = createHashMap<pthread_t,T>();
    mutex = createMutex("ThreadLocalMutex");
}

template<typename T>
void _ThreadLocal<T>::set(pthread_t pthread,T t){
    AutoLock l(mutex);
    mLocalMap->put(pthread,t);
}


template<typename T>
void _ThreadLocal<T>::set(T t){
    AutoLock l(mutex);
    mLocalMap->put(pthread_self(),t);
}

template<typename T>
void _ThreadLocal<T>::remove(pthread_t ptread){
    AutoLock l(mutex);
    mLocalMap->remove(ptread);
}

template<typename T>
void _ThreadLocal<T>::remove(){
    AutoLock l(mutex);
    mLocalMap->remove(pthread_self());
}

template<typename T>
T _ThreadLocal<T>::get(){
    AutoLock l(mutex);
    return mLocalMap->get(pthread_self());
}

template<typename T>
T _ThreadLocal<T>::get(pthread_t t){
    AutoLock l(mutex);
    return mLocalMap->get(t);
}

template<typename T>
int _ThreadLocal<T>::size(){
    AutoLock l(mutex);
    return mLocalMap->size();
}

template<typename T>
_ThreadLocal<T>::~_ThreadLocal(){
    AutoLock l(mutex);
    mLocalMap->clear(); 
}

template<typename T>
void _ThreadLocal<T>::clear(){
    AutoLock l(mutex);
    mLocalMap->clear();
}

}
#endif