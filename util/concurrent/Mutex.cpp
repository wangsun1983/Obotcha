#include <stdio.h>

#include "Mutex.hpp"

namespace obotcha {

_Mutex::_Mutex(){
    pthread_mutex_init(&mutex_t, NULL);
}

_Mutex::_Mutex(String v){
    pthread_mutex_init(&mutex_t, NULL);
    mMutexName = v;
}

pthread_mutex_t* _Mutex::getMutex_t() {
    return &mutex_t;
}

void _Mutex::lock() {
    pthread_mutex_lock(&mutex_t);
}

void _Mutex::unlock() {
    pthread_mutex_unlock(&mutex_t);
}

bool _Mutex::trylock() {
    //TODO
    pthread_mutex_trylock(&mutex_t);
    return true;
}

_Mutex::~_Mutex() {
    if(mMutexName == nullptr) {
        printf("release Mutex\n");    
    } else {
        printf("release Mutex: %s,id is %x\n",mMutexName->toChars(),&mutex_t);    
    }
    
    pthread_mutex_destroy(&mutex_t);
}

}