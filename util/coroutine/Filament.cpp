#include "Filament.hpp"

namespace obotcha {

void _Filament::start() {
    co_create(&coa, nullptr, localFilaRun, this);
    co_resume(coa);
}

void _Filament::start(FilaFuture future) {
    printf("Filament start trace1 \n");
    mFuture = future;
    printf("Filament start trace2 \n");
    if(mFuture != nullptr) {
        printf("Filament start trace3 \n");
    }
    co_create(&coa, nullptr, localFilaRun, this);
    mFuture->setOwner(coa);
    co_resume(coa);
}


void *_Filament::localFilaRun(void *args) {
    printf("localFilaRun start \n");
    _Filament *fila = static_cast<_Filament *>(args);
    fila->run();
    printf("localFilaRun start2 \n");
    if(fila->mFuture != nullptr) {
        printf("localFilaRun start3 \n");
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
    co_release(coa); 
}

} // namespace obotcha