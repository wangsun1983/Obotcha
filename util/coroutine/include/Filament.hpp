#ifndef __OBOTCHA_FILAMENT_HPP__
#define __OBOTCHA_FILAMENT_HPP__

#include "co_routine.h"

#include "StrongPointer.hpp"
#include "Object.hpp"
#include "Runnable.hpp"
#include "String.hpp"

namespace obotcha {

class _FilaCroutine;

DECLARE_SIMPLE_CLASS(Filament) {

public:
    friend class _FilaCroutine;

    _Filament(Runnable);

    _Filament(String,Runnable);

    void start();

    void resume();

    void yield();

    void destroy();

private:
    static void *localFilaRun(void *args);

    stCoRoutine_t *coa;

    Runnable mRun;

    String mName;
};

}
#endif