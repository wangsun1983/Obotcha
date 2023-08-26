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
    
    _FilaMutex() = default;
    
    int lock(long interval = 0) override;

    int unlock() override;

    bool isOwner() override;
private:
    Mutex mMutex = createMutex();
    stCoRoutine_t *owner = nullptr;
};

} // namespace obotcha
#endif
