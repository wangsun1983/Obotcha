#ifndef __OBOTCHA_FILA_CROUTINE_HPP__
#define __OBOTCHA_FILA_CROUTINE_HPP__

#include "co_routine.h"

#include "ArrayList.hpp"
#include "Filament.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Thread.hpp"
#include "FilaFuture.hpp"
#include "FilaCondition.hpp"
#include "FilaExecutorResult.hpp"

namespace obotcha {

//class _FilaCondition;

DECLARE_CLASS(FilaRoutineInnerEvent) {
public:
  enum {
      NewTask = 0,
      Notify,
      NotifyAll,
      RemoveFilament,
      Stop,
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

    template <class Function, class... Args>
    FilaFuture submit(Function && f, Args && ... args){
        auto filament = createLambdaFilament(f, args...);
        return submit(filament);
    }

    void start();

    void run();

    void stop();

    void onInterrupt();
    
    void onComplete();
  
    void postEvent(FilaRoutineInnerEvent);

    void removeFilament(Filament);

    int getFilamentSize();

    ~_FilaRoutine();
    
  private:
    Mutex mDataMutex;
    FilaMutex mFilaMutex;
    ArrayList<Filament> mFilaments;
    ArrayList<FilaRoutineInnerEvent> innerEvents;
    //volatile bool isStop;

    static int onIdle(void *);
};

} // namespace obotcha
#endif