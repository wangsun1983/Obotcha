#ifndef __THREAD_LOCAL_HPP__
#define __THREAD_LOCAL_HPP__

#include <vector>
#include <pthread.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "HashMap.hpp"
#include "Mutex.hpp"
#include "AutoMutex.hpp"

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
    AutoMutex l(mutex);
    mLocalMap->put(pthread,t);
}


template<typename T>
void _ThreadLocal<T>::set(T t){
    AutoMutex l(mutex);
    mLocalMap->put(pthread_self(),t);
}

template<typename T>
void _ThreadLocal<T>::remove(pthread_t ptread){
    AutoMutex l(mutex);
    mLocalMap->remove(ptread);
}

template<typename T>
void _ThreadLocal<T>::remove(){
    AutoMutex l(mutex);
    mLocalMap->remove(pthread_self());
}

template<typename T>
T _ThreadLocal<T>::get(){
    AutoMutex l(mutex);
    return mLocalMap->get(pthread_self());
}

template<typename T>
T _ThreadLocal<T>::get(pthread_t t){
    AutoMutex l(mutex);
    return mLocalMap->get(t);
}

template<typename T>
int _ThreadLocal<T>::size(){
    AutoMutex l(mutex);
    return mLocalMap->size();
}

template<typename T>
_ThreadLocal<T>::~_ThreadLocal(){
    printf("thread local distroy \n");
}


}
#endif