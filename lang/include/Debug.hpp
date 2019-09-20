#ifndef __DEBUG_HPP__
#define __DEBUG_HPP__

#include <pthread.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"

namespace obotcha {

//config
#define THREAD_COUNT_DEBUG


class DebugInternalAutoLock {
public:
    DebugInternalAutoLock(pthread_mutex_t t) {
        pthread_mutex_lock(&t);
        mutex = t;
    }

    ~DebugInternalAutoLock() {
        pthread_mutex_unlock(&mutex);
    }

private:
    pthread_mutex_t mutex;

};

#ifdef THREAD_COUNT_DEBUG
//Reference Debug Function declaration
#define DEBUG_REFERENCE_DECLARATION \
    static void initDebugReferenceCount();\
    static void incDebugReferenctCount();\
    static void decDebugReferenctCount();\
    static int getDebugReferenceCount();\
    static pthread_mutex_t referenceCountMutex;\
    static int debugReferenceCount;
#else 
    #define DEBUG_REFERENCE_DECLARATION
#endif    

#ifdef THREAD_COUNT_DEBUG
#define DEBUG_REFERENCE_REALIZATION(C) \
pthread_mutex_t _##C::referenceCountMutex = PTHREAD_MUTEX_INITIALIZER;\
int _##C::debugReferenceCount = 0;\
\
void _##C::initDebugReferenceCount() { \
    debugReferenceCount = 0; \
}\
\
void _##C::incDebugReferenctCount() {\
    DebugInternalAutoLock ll(referenceCountMutex);\
    debugReferenceCount++;\
}\
void _##C::decDebugReferenctCount() {\
    DebugInternalAutoLock ll(referenceCountMutex);\
    debugReferenceCount--;\
}\
int _##C::getDebugReferenceCount() {\
    return debugReferenceCount;\
}\

#else
#define DEBUG_REFERENCE_REALIZATION(C)
#endif

}

#endif
