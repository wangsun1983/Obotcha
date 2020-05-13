#ifndef __OBOTCHA_FILAMENT_HPP__
#define __OBOTCHA_FILAMENT_HPP__

#include "co_routine.h"

#include "StrongPointer.hpp"
#include "Object.hpp"
#include "Runnable.hpp"
#include "FilaRunnable.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Filament) {

public:
    _Filament(FilaRunnable);

    _Filament(String,FilaRunnable);

    //void create(FilaRunnable);

    void resume();

    void yield();

    void destroy();

    static void yieldCurrent();

private:

    static void* localFilaRun(void *);

    stCoRoutine_t *coa;

    FilaRunnable mRun;

    String mName;
};

}
#endif