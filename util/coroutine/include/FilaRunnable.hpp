#ifndef __OBOTCHA_FILA_RUNNABLE_HPP__
#define __OBOTCHA_FILA_RUNNABLE_HPP__

#include "co_routine.h"

#include "StrongPointer.hpp"
#include "Object.hpp"
#include "Runnable.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(FilaRunnable) {

public:
    virtual void run() = 0;
};

}
#endif