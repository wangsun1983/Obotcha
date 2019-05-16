#ifndef __FILA_RUNNABLE_HPP__
#define __FILA_RUNNABLE_HPP__

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