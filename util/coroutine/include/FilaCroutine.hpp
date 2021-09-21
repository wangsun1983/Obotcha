#ifndef __OBOTCHA_FILA_CROUTINE_HPP__
#define __OBOTCHA_FILA_CROUTINE_HPP__

#include "co_routine.h"

#include "ArrayList.hpp"
#include "Filament.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Thread.hpp"

namespace obotcha {

DECLARE_CLASS(FilaCroutine) IMPLEMENTS(Thread) {

  public:
    _FilaCroutine(ArrayList<Filament>);
    void start();

    void run();

    void onInterrupt();

  private:
    ArrayList<Filament> mFilaments;
};

} // namespace obotcha
#endif