#ifndef __OBOTCHA_FILA_CROUTINE_HPP__
#define __OBOTCHA_FILA_CROUTINE_HPP__

#include "co_routine.h"

#include "Object.hpp"
#include "ArrayList.hpp"
#include "Filament.hpp"
#include "Thread.hpp"
#include "FilaFuture.hpp"
#include "FilaCondition.hpp"

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
    
    _FilaRoutineInnerEvent(int e,Filament f,FilaCondition c);
    
    int event;
    Filament filament;
    FilaCondition cond;
};

DECLARE_CLASS(FilaRoutine) IMPLEMENTS(Thread) {

  public:
    _FilaRoutine();
    
    template <typename X>
    FilaFuture submit(sp<X> f) {
        FilaRoutineInnerEvent event = createFilaRoutineInnerEvent(
            st(FilaRoutineInnerEvent)::NewTask,
            f,
            nullptr
        );
        //event->event = st(FilaRoutineInnerEvent)::NewTask;
        //event->filament = f;
        auto future = event->filament->genFuture();
        innerEvents->add(event);
        return future;
    }

    template <typename X>
    void execute(sp<X> f) {
        AutoLock l(mDataMutex);
        //FilaRoutineInnerEvent event = createFilaRoutineInnerEvent();
        //event->event = st(FilaRoutineInnerEvent)::NewTask;
        //event->filament = f;
        auto event = createFilaRoutineInnerEvent(
              st(FilaRoutineInnerEvent)::NewTask,
              f,
              nullptr);
        innerEvents->add(event);
    }

    template <class Function, class... Args>
    void execute(Function && f, Args && ... args){
        auto filament = createLambdaFilament(f, args...);
        execute(filament);
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
    
    static int onIdle(void *);
};

} // namespace obotcha
#endif