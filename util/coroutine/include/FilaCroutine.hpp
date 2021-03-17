#ifndef __OBOTCHA_FILA_CROUTINE_HPP__
#define __OBOTCHA_FILA_CROUTINE_HPP__

#include "co_routine.h"

#include "StrongPointer.hpp"
#include "Object.hpp"
#include "ArrayList.hpp"
#include "Filament.hpp"
#include "Thread.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(FilaCroutine) IMPLEMENTS(Thread){

public:
    _FilaCroutine(ArrayList<Filament>);
    void start();

    void run();
    
    void onInterrupt();

private:
    ArrayList<Filament> mFilaments;
};

}
#endif