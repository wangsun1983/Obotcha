#ifndef __OBOTCHA_FILA_CROUTINE_HPP__
#define __OBOTCHA_FILA_CROUTINE_HPP__

#include "co_routine.h"

#include "ArrayList.hpp"
#include "Filament.hpp"
#include "FilaCondition.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Thread.hpp"

namespace obotcha {

DECLARE_CLASS(FilaCoutineInnerEvent) {
public:
  enum {
    NewTask = 0,
    Notify,
    NotifyAll
  };

  int event;
  Filament filament;
  FilaCondition cond;
};

DECLARE_CLASS(FilaCroutine) IMPLEMENTS(Thread) {

  public:
    _FilaCroutine();

    void submit(Filament);

    template <class Function, class... Args>
    void submit(Function && f, Args && ... args){
        auto filament = createLambdaFilament(f, args...);
        submit(filament);
    }

    void start();

    void run();

    void onInterrupt();
    void postEvent(FilaCoutineInnerEvent);
    
  private:
    Mutex mDataMutex;
    ArrayList<Filament> mFilaments;
    ArrayList<FilaCoutineInnerEvent> innerEvents;
    
    static void onIdle(void *);
};

} // namespace obotcha
#endif