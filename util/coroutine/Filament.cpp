#include "Filament.hpp"

namespace obotcha {

_Filament::_Filament() {
    coa = nullptr;
}

void _Filament::start() {
    co_create(&coa, nullptr, localFilaRun, this);
    co_resume(coa);
}

void _Filament::start(FilaFuture future) {
    mFuture = future;
    co_create(&coa, nullptr, localFilaRun, this);
    mFuture->setOwner(coa);
    co_resume(coa);
}

void *_Filament::localFilaRun(void *args) {
    _Filament *fila = static_cast<_Filament *>(args);
    fila->run();
    if(fila->mFuture != nullptr) {
        fila->mFuture->wakeAll();
    }
    return nullptr;
}

void _Filament::resume() { 
    co_resume(coa); 
}

void _Filament::yield() { 
    co_yield(coa); 
}

void _Filament::destroy() { 
    if(coa != nullptr) {
        co_release(coa); 
        coa = nullptr;
    }
}

_Filament::~_Filament() {
    destroy();
}

} // namespace obotcha