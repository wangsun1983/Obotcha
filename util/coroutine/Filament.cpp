#include "Filament.hpp"

namespace obotcha {

void _Filament::start() {
    co_create(&coa, nullptr, localFilaRun, this);
    co_resume(coa);
}

void *_Filament::localFilaRun(void *args) {
    _Filament *fila = static_cast<_Filament *>(args);
    fila->run();
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