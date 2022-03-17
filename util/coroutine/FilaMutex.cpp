#include "co_routine_inner.h"
#include "FilaMutex.hpp"
#include "Filament.hpp"
#include "System.hpp"

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
            //AutoLock l(mOwnerMutex);
            mOwnerMutex->lock();
            if(owner == nullptr) {
                owner = coa;
                mOwnerMutex->unlock();
                mMutex->lock();
                break;
            }else if(owner == coa) {
                mOwnerMutex->unlock();
                mMutex->lock();
                break;
            }
            mOwnerMutex->unlock();
            poll(NULL, 0, 1);
        }
    }

    return 0;
}

int _FilaMutex::unlock() {
    auto coa = GetCurrThreadCo();
    AutoLock l(mOwnerMutex);
    if(owner == coa || coa == nullptr) {
        owner = nullptr;
        mMutex->unlock();
    }
    return 0;
}

} // namespace obotcha
