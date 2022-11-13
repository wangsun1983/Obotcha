#ifndef __OBOTCHA_FILA_MUTEX_HPP__
#define __OBOTCHA_FILA_MUTEX_HPP__

#include "co_routine.h"

#include "Object.hpp"
#include "Runnable.hpp"
#include "Lock.hpp"
#include "Mutex.hpp"

namespace obotcha {

class _FilaCroutine;
class _Filament;
class _FilaCondtion;

DECLARE_CLASS(FilaMutex) IMPLEMENTS(Lock){
public:
    friend class _FilaCondition;
    
    _FilaMutex();
    
    int lock(long interval = 0);

    int unlock();

    bool isOwner();
private:
    Mutex mMutex;
    stCoRoutine_t *owner;
};

} // namespace obotcha
#endif
