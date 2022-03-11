#ifndef __OBOTCHA_FILA_CONDITION_HPP__
#define __OBOTCHA_FILA_CONDITION_HPP__

#include <map>
#include "co_routine.h"

#include "Object.hpp"
#include "Runnable.hpp"
#include "StrongPointer.hpp"
#include "ThreadLocal.hpp"
#include "FilaMutex.hpp"
#include "Condition.hpp"

namespace obotcha {

class _FilaCroutine;

DECLARE_CLASS(FilaCondition) {

  public:
    friend class _FilaRoutine;
    _FilaCondition();
    void wait(FilaMutex);
    void wait(FilaMutex,long mseconds);
    void notify();
    void notifyAll();
    ~_FilaCondition();

  private:
    stCoCond_t *mCond;

    void doNotifyAll();
    void doNotify();

    Condition mOriCond;
};

} // namespace obotcha
#endif
