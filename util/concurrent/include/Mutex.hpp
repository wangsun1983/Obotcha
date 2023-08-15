/**
 * @file Mutex.cpp
 * @brief  Mutex is a tool for controlling access to a shared resource by
 * multiple threads
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */
#ifndef __OBOTCHA_MUTEX_HPP__
#define __OBOTCHA_MUTEX_HPP__

#include <pthread.h>

#include "Object.hpp"
#include "Lock.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(Mutex) IMPLEMENTS(Lock) {
public:
    friend class _Condition;

    explicit _Mutex(String,  st(Lock)::Type type = st(Lock)::Type::Recursive);

    explicit _Mutex(const char *,  st(Lock)::Type type = st(Lock)::Type::Recursive);

    explicit _Mutex(st(Lock)::Type type = st(Lock)::Type::Recursive);

    int lock(long interval = 0) override;

    int unlock() override;

    int tryLock();

    bool isOwner() override;

    ~_Mutex() override;

    String getName();

private:
    pthread_mutex_t *getMutex_t();

    pthread_mutex_t mutex_t;

    pthread_mutexattr_t mutex_attr;

    String mMutexName;
};

} // namespace obotcha
#endif