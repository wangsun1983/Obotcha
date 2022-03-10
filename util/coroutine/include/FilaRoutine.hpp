#ifndef __OBOTCHA_FILA_CROUTINE_HPP__
#define __OBOTCHA_FILA_CROUTINE_HPP__

#include "co_routine.h"

#include "ArrayList.hpp"
#include "Filament.hpp"
#include "FilaCondition.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Thread.hpp"
#include "FilaFuture.hpp"

namespace obotcha {


void filaSleep(long);

DECLARE_CLASS(FilaRoutineInnerEvent) {
public:
  enum {
    NewTask = 0,
    Notify,
    NotifyAll
  };

  int event;
  Filament filament;
  FilaCondition cond;
  FilaFuture future;
};

DECLARE_CLASS(FilaRoutine) IMPLEMENTS(Thread) {

  public:
    _FilaRoutine();

    template <typename X>
    FilaFuture submit(sp<X> f) {
      FilaFuture future = createFilaFuture();
      FilaRoutineInnerEvent event = createFilaRoutineInnerEvent();
      event->event = st(FilaRoutineInnerEvent)::NewTask;
      event->filament = f;
      event->future = future;
      innerEvents->add(event);
      return future;
    }

    template <typename X>
    void execute(sp<X> f) {
        AutoLock l(mDataMutex);
        FilaRoutineInnerEvent event = createFilaRoutineInnerEvent();
        event->event = st(FilaRoutineInnerEvent)::NewTask;
        event->filament = f;
        innerEvents->add(event);
    }

    template <class Function, class... Args>
    void execute(Function && f, Args && ... args){
        auto filament = createLambdaFilament(f, args...);
        submit(filament);
    }

    void start();

    void run();

    void onInterrupt();
    void onComplete();
  
    void postEvent(FilaRoutineInnerEvent);

    ~_FilaRoutine();
    
  private:
    Mutex mDataMutex;
    ArrayList<Filament> mFilaments;
    ArrayList<FilaRoutineInnerEvent> innerEvents;
    
    static void onIdle(void *);
};

} // namespace obotcha
#endif