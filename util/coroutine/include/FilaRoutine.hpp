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

DECLARE_CLASS(FilaRoutineInnerEvent) {
public:
    enum class Type {
        NewTask = 0,
        Notify,
        NotifyAll,
        RemoveFilament,
        Stop,
    };
    
    _FilaRoutineInnerEvent(_FilaRoutineInnerEvent::Type e,Filament f,FilaCondition c);
    
    _FilaRoutineInnerEvent::Type event;
    Filament filament;
    FilaCondition cond;
};

DECLARE_CLASS(FilaRoutine) IMPLEMENTS(Thread) {

  public:
    _FilaRoutine() = default;
    
    template <typename X>
    FilaFuture submit(sp<X> f) {
        FilaRoutineInnerEvent event = createFilaRoutineInnerEvent(
            st(FilaRoutineInnerEvent)::Type::NewTask,
            f,
            nullptr
        );

        auto future = event->filament->genFuture();
        innerEvents->add(event);
        return future;
    }

    template <typename X>
    void execute(sp<X> f) {
        AutoLock l(mDataMutex);
        auto event = createFilaRoutineInnerEvent(
              st(FilaRoutineInnerEvent)::Type::NewTask,
              f,
              nullptr);
        innerEvents->add(event);
    }

    template <class Function, class... Args>
    void execute(Function f, Args... args){
        _Filament *r = new _LambdaFilament<Function, Args...>(f,args...);
        execute(AutoClone(r));
    }

    template <class Function, class... Args>
    FilaFuture submit(Function f, Args... args){
        _Filament *r = new _LambdaFilament<Function, Args...>(f,args...);
        return submit(AutoClone(r));
    }

    void run() override;

    void stop();

    //void onInterrupt();
    
    void onComplete() override;
  
    void postEvent(FilaRoutineInnerEvent);

    void removeFilament(Filament);

    int getFilamentSize();

    ~_FilaRoutine() override;
    
  private:
    Mutex mDataMutex = createMutex();
    FilaMutex mFilaMutex = createFilaMutex();
    ArrayList<Filament> mFilaments = createArrayList<Filament>();
    ArrayList<FilaRoutineInnerEvent> innerEvents = createArrayList<FilaRoutineInnerEvent>();
    
    static int OnIdle(void *);
};

} // namespace obotcha
#endif