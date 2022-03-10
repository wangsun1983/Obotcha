#include "co_routine_inner.h"
#include "FilaMutex.hpp"
#include "Filament.hpp"

namespace obotcha {

_FilaMutex::_FilaMutex() {
    mMutex = createMutex();
    mOwnerMutex = createMutex();
    owner = nullptr;
}

int _FilaMutex::lock() {
    auto coa = GetCurrThreadCo();
    if(coa == nullptr) {
        //it is not a routine
        mMutex->lock();
    } else {
        while(1) {
            AutoLock l(mOwnerMutex);

            if(owner == nullptr) {
                owner = coa;
                mMutex->lock();
                break;
            }else if(owner == coa) {
                mMutex->lock();
                break;
            }
            poll(NULL, 0, 1);
        }
    }

    return 0;
}

int _FilaMutex::unlock() {
    auto coa = GetCurrThreadCo();
    AutoLock l(mOwnerMutex);
    if(owner == coa) {
        owner = nullptr;
        mMutex->unlock();
    }
    return 0;
}


} // namespace obotcha
