#ifndef __OBOTCHA_FILA_CONDITION_HPP__
#define __OBOTCHA_FILA_CONDITION_HPP__

#include "co_routine.h"

#include "StrongPointer.hpp"
#include "Object.hpp"
#include "Runnable.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(FilaCondition) {

public:
    _FilaCondition();
    void wait();
    void wait(long mseconds);
    void notify();
    void notifyAll();
    ~_FilaCondition();

private:
   stCoCond_t* mCond;
};

}
#endif
