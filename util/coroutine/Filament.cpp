#include "Filament.hpp"
#include "FilaRoutine.hpp"

namespace obotcha {

_Filament::_Filament() {
    coa = nullptr;
    mFuture = nullptr;
}

bool _Filament::onInterrupt() {
    if(mFuture != nullptr) {
        mFuture->setStatus(st(FilaFuture)::Interrupt);
        mFuture->wakeAll();
    }

    return true;
}

void _Filament::start(FilaFuture future) {
    mFuture = future;
    co_create(&coa, nullptr, localFilaRun, this);
    if(mFuture != nullptr) {
        mFuture->setStatus(st(FilaFuture)::Running);
        mFuture->setOwner(coa);
        st(FilaExecutorResult)::bindResult(coa,mFuture->genResult());
    }
    co_resume(coa);
}

void *_Filament::localFilaRun(void *args) {
    _Filament *fila = static_cast<_Filament *>(args);
    fila->run();
    if(fila->mFuture != nullptr) {
        fila->mFuture->setStatus(st(FilaFuture)::Complete);
        st(FilaExecutorResult)::unBindResult(GetCurrThreadCo());
        fila->mFuture->wakeAll();
    }

    //remove myself from routine's filaments
    auto routine = Cast<FilaRoutine>(st(Thread)::current());
    //auto routine = st(FilaRoutineManager)::getInstance()->getRoutine();
    if(routine != nullptr) {
        //routine->removeFilament(AutoClone(fila));
        FilaRoutineInnerEvent event = createFilaRoutineInnerEvent();
        event->event = st(FilaRoutineInnerEvent)::RemoveFilament;
        event->filament = AutoClone(fila);
        routine->postEvent(event);
    }
    return nullptr;
}

void _Filament::resume() { 
    co_resume(coa); 
}

void _Filament::yield() { 
    co_yield(coa); 
}

_Filament::~_Filament() {
    if(coa != nullptr) {
        co_release(coa);
        coa = nullptr;
    }
}

void _Filament::markAsReleased() {
    //released by stopping FilaRoutine 
    coa = nullptr;
}

} // namespace obotcha