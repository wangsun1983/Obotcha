#ifndef __OBOTCHA_FILA_CONDITION_HPP__
#define __OBOTCHA_FILA_CONDITION_HPP__

#include "co_routine.h"

#include "Object.hpp"
#include "Runnable.hpp"
#include "StrongPointer.hpp"
#include "ThreadLocal.hpp"

namespace obotcha {

class _FilaCroutine;

DECLARE_CLASS(FilaCondition) {

  public:
    friend class _FilaCroutine;
    _FilaCondition();
    void wait();
    void wait(long mseconds);
    void notify();
    void notifyAll();
    ~_FilaCondition();

  private:
    stCoCond_t *mCond;
    void doNotifyAll();
    void doNotify();
};

} // namespace obotcha
#endif
