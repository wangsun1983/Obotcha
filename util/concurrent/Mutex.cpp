#include <stdio.h>

#include "Mutex.hpp"

namespace obotcha {

_Mutex::_Mutex():mutex_t(PTHREAD_MUTEX_INITIALIZER){
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

}