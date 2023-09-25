#ifndef __OBOTCHA_FILA_CROUTINE_HPP__
#define __OBOTCHA_FILA_CROUTINE_HPP__

#include "co_routine.h"

#include "Object.hpp"
#include "ArrayList.hpp"
#include "Filament.hpp"
#include "Thread.hpp"
#include "FilaFuture.hpp"
#include "LinkedList.hpp"

namespace obotcha {

DECLARE_CLASS(FilaRoutineInnerEvent) {
public:
    enum class Type {
        NewTask = 0,
        Notify,
        NotifyAll,
        RemoveFilament,
        Shutdown,
        Release,
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
        //Inspect(isShutdown == 1,nullptr)
        FilaRoutineInnerEvent event = createFilaRoutineInnerEvent(
            st(FilaRoutineInnerEvent)::Type::NewTask,
            f,
            nullptr
        );

        auto future = event->filament->genFuture();
        innerEvents->putLast(event);
        return future;
    }

    template <typename X>
    void execute(sp<X> f) {
        //Inspect(isShutdown == 1)
        AutoLock l(mDataMutex);
        auto event = createFilaRoutineInnerEvent(
              st(FilaRoutineInnerEvent)::Type::NewTask,
              f,
              nullptr);
        innerEvents->putLast(event);
    }

    template <class Function, class... Args>
    void execute(Function f, Args... args){
        //Inspect(isShutdown == 1)
        _Filament *r = new _LambdaFilament<Function, Args...>(f,args...);
        execute(AutoClone(r));
    }

    template <class Function, class... Args>
    FilaFuture submit(Function f, Args... args){
        //Inspect(isShutdown == 1,nullptr)
        _Filament *r = new _LambdaFilament<Function, Args...>(f,args...);
        return submit(AutoClone(r));
    }

    void run() override;

    void shutdown();
    bool isTerminated();
    int awaitTermination(long timeout = st(Concurrent)::kWaitForEver);
    
    void onComplete() override;
  
    void postEvent(FilaRoutineInnerEvent);

    void removeFilament(Filament);

    int getFilamentSize();

    ~_FilaRoutine() override;
    
  private:
    enum class LocalStatus {
        Running = 0,
        Shutdown,
        Terminated
    };

    static int OnIdle(void *);
    
    Mutex mDataMutex = createMutex();
    FilaMutex mFilaMutex = createFilaMutex();
    ArrayList<Filament> mFilaments = createArrayList<Filament>();
    LinkedList<FilaRoutineInnerEvent> innerEvents = createLinkedList<FilaRoutineInnerEvent>();
    
    std::atomic<LocalStatus> mStatus = LocalStatus::Running; 
    stCoRoutineEnv_t *mEnv = nullptr;
    
};

} // namespace obotcha
#endif