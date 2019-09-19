#ifndef __DEBUG_HPP__
#define __DEBUG_HPP__

#include <pthread.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"

namespace obotcha {

//config
#define THREAD_COUNT_DEBUG

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
    pthread_mutex_lock(&referenceCountMutex);\
    debugReferenceCount++;\
    pthread_mutex_unlock(&referenceCountMutex);\
}\
void _##C::decDebugReferenctCount() {\
    pthread_mutex_lock(&referenceCountMutex);\
    debugReferenceCount--;\
    pthread_mutex_unlock(&referenceCountMutex);\
}\
int _##C::getDebugReferenceCount() {\
    return debugReferenceCount;\
}\

#else
#define DEBUG_REFERENCE_REALIZATION(C)
#endif

}

#endif
