#include "Filament.hpp"
#include "FilaRoutineManager.hpp"

namespace obotcha {

_Filament::_Filament() {
    coa = nullptr;
    mFuture = nullptr;
}

bool _Filament::onInterrupt() {
    if(mFuture != nullptr) {
        mFuture->setResultType(st(FilaFuture)::Interrupt);
        mFuture->wakeAll();
    }

    return true;
}

void _Filament::start() {
    co_create(&coa, nullptr, localFilaRun, this);
    co_resume(coa);
}

void _Filament::start(FilaFuture future) {
    mFuture = future;
    co_create(&coa, nullptr, localFilaRun, this);
    if(mFuture != nullptr) {
        mFuture->setOwner(coa);
    }
    co_resume(coa);
}

void *_Filament::localFilaRun(void *args) {
    _Filament *fila = static_cast<_Filament *>(args);
    fila->run();
    if(fila->mFuture != nullptr) {
        fila->mFuture->wakeAll();
    }
    printf("localfinal run \n");
    //remove myself from routine's filaments
    auto routine = st(FilaRoutineManager)::getInstance()->getRoutine();
    printf("localfinal run1 \n");
    if(routine != nullptr) {
        printf("localfinal run2 \n");
        //routine->removeFilament(AutoClone(fila));
        FilaRoutineInnerEvent event = createFilaRoutineInnerEvent();
        event->event = st(FilaRoutineInnerEvent)::RemoveFilament;
        event->filament = AutoClone(fila);
        routine->postEvent(event);
    }
    printf("localfinal run3 \n");
    return nullptr;
}

void _Filament::resume() { 
    co_resume(coa); 
}

void _Filament::yield() { 
    co_yield(coa); 
}

void _Filament::destroy() { 
    printf("filament destroy1 \n");
    if(coa != nullptr) {
        printf("filament destroy2\n");
        co_release(coa);
        printf("filament destroy3 \n");
        coa = nullptr;
    }
}

_Filament::~_Filament() {
    printf("filament  \n");
    destroy();
}

} // namespace obotcha