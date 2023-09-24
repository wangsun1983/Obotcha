#include "Filament.hpp"
#include "FilaRoutine.hpp"

namespace obotcha {

bool _Filament::onInterrupt() {
    if(mFuture != nullptr) {
        mFuture->setStatus(st(Concurrent)::Status::Interrupt);
        mFuture->wakeAll();
    }

    return true;
}

void _Filament::start() {
    co_create(&coa, nullptr, localFilaRun, this);
    if(mFuture != nullptr) {
        mFuture->setStatus(st(Concurrent)::Status::Running);
        mFuture->setOwner(coa);
        st(FilaExecutorResult)::BindResult(coa,mFuture->genResult());
    }
    co_resume(coa);
}

void *_Filament::localFilaRun(void *args) {
    auto fila = static_cast<_Filament *>(args);
    fila->run();
    if(fila->mFuture != nullptr) {
        fila->mFuture->setStatus(st(Concurrent)::Status::Complete);
        st(FilaExecutorResult)::UnBindResult(GetCurrThreadCo());
        fila->mFuture->wakeAll();
    }

    //remove myself from routine's filaments
    auto routine = Cast<FilaRoutine>(st(Thread)::Current());
    if(routine != nullptr) {
        auto event = createFilaRoutineInnerEvent(
                            st(FilaRoutineInnerEvent)::Type::RemoveFilament,
                            AutoClone(fila),
                            nullptr);
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

void _Filament::run() {
    // Intentionally unimplemented...
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

FilaFuture _Filament::getFuture() {
    return mFuture;
}

FilaFuture _Filament::genFuture() {
    mFuture = createFilaFuture();
    return mFuture;
}

} // namespace obotcha