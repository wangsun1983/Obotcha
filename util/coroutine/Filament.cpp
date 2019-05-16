#include "Filament.hpp"

namespace obotcha {

_Filament::_Filament(String name,FilaRunnable r) {
    mName = name;
    mRun = r;
    co_create(&coa,NULL,localFilaRun,this);
}

_Filament::_Filament(FilaRunnable r) {
    mRun = r;
    co_create(&coa,NULL,localFilaRun,this);
}

void *_Filament::localFilaRun(void *args) {
    _Filament *fila = static_cast<_Filament *>(args);
    if(fila->mRun != nullptr) {
        fila->mRun->run();
    }
}

//void _Filament::create(FilaRunnable r) {
//    mRun = r;
//    co_create(&coa,NULL,localFilaRun,this);
//}

void _Filament::resume() {
    co_resume(coa);
}

void _Filament::yield() {
    co_yield(coa);
}

void _Filament::destroy() {
    co_release(coa);
}

void _Filament::yieldCurrent() {
    co_yield_ct();
}

}