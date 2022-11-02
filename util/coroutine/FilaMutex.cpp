#include "co_routine_inner.h"
#include "FilaMutex.hpp"
#include "Filament.hpp"
#include "Fila.hpp"
#include "System.hpp"

namespace obotcha {

_FilaMutex::_FilaMutex() {
    mMutex = createMutex();
    owner = nullptr;
}

int _FilaMutex::lock(long interval) {
    auto coa = GetCurrThreadCo();
    if(coa == nullptr) {
        //it is not a routine
        mMutex->lock(interval);
    } else {
        bool isWaitForEver = (interval == 0);
        while(1) {
            if(!isWaitForEver && interval == 0) {
                return -ETIMEDOUT;
            }
            if(mMutex->isOwner() || mMutex->tryLock() == 0) {
                if(owner == nullptr || owner == coa) {
                    owner = coa;
                    break;
                }
            }
            if(!isWaitForEver) {
                interval--;
            }
            st(Fila)::sleep(1);
        }
    }

    return 0;
}

bool _FilaMutex::isOwner() {
    auto current = GetCurrThreadCo();
    if(owner != nullptr && current == owner) {
        return true;
    }

    if(mMutex->isOwner() && current == nullptr) {
        return true;
    }

    return false;
}

int _FilaMutex::unlock() {
    if(GetCurrThreadCo() == owner) {
        owner = nullptr;
    }

    if(mMutex->isOwner()) {
        mMutex->unlock();
    }

    return 0;
}

} // namespace obotcha
