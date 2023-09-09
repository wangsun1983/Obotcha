#include "co_routine_inner.h"
#include "FilaMutex.hpp"
#include "Filament.hpp"
#include "Fila.hpp"
#include "System.hpp"

namespace obotcha {

int _FilaMutex::lock(long interval) {
    if(auto coa = GetCurrThreadCo();coa == nullptr) {
        //it is not a routine
        mMutex->lock(interval);
    } else {
        bool isWaitForEver = (interval == 0);
        while(true) {
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
