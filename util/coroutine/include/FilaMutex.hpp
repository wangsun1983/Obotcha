#ifndef __OBOTCHA_FILA_MUTEX_HPP__
#define __OBOTCHA_FILA_MUTEX_HPP__

#include "co_routine.h"

#include "Object.hpp"
#include "Runnable.hpp"
#include "StrongPointer.hpp"
#include "ThreadLocal.hpp"
#include "Lock.hpp"
#include "AtomicInteger.hpp"

namespace obotcha {

class _FilaCroutine;
class _Filament;
class _FilaCondtion;

DECLARE_CLASS(FilaMutex) IMPLEMENTS(Lock){
public:
    friend class _FilaCondition;
    _FilaMutex();
    int lock();
    int unlock();

private:
    Mutex mMutex;
    Mutex mOwnerMutex;
    stCoRoutine_t *owner;
    //void setOwner(stCoRoutine_t *);
};

} // namespace obotcha
#endif