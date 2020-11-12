#include "Filament.hpp"

namespace obotcha {

_Filament::_Filament(String name,Runnable r) {
    mName = name;
    mRun = r;
}

_Filament::_Filament(Runnable r) {
    mRun = r;
}

void _Filament::start() {
    co_create(&coa,nullptr,localFilaRun,this);
    co_resume(coa);
}

void *_Filament::localFilaRun(void *args) {
    _Filament *fila = static_cast<_Filament *>(args);
    if(fila->mRun != nullptr) {
        fila->mRun->run();
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

}