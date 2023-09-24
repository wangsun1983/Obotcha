#include "co_routine_inner.h"
#include "FilaMutex.hpp"
#include "Filament.hpp"
#include "Fila.hpp"
#include "System.hpp"
#include "IllegalStateException.hpp"

namespace obotcha {

int _FilaMutex::lock(long interval) {
    if(auto coa = GetCurrThreadCo();coa == nullptr) {
        //it is not a routine
        mMutex->lock(interval);
    } else {
        bool isWaitForEver = (interval == 0);
        while(true) {
            if(!isWaitForEver && interval <= 0) {
                return -ETIMEDOUT;
            }
            if(mMutex->isOwner() || mMutex->tryLock() == 0) {
                if(owner == nullptr || owner == coa) {
                    owner = coa;
                    mCount++;
                    break;
                }
            }
            if(!isWaitForEver) {
                interval-= 10;
            }
            st(Fila)::Sleep(10);
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
    auto current = GetCurrThreadCo();
    if(current != nullptr) {
        if(current == owner) {
            if(mCount == 1) {
                owner = nullptr;
            }
            mCount--;
        } else {
            Trigger(IllegalStateException,"not owner")
        }
    }

    if(mMutex->isOwner()) {
        mMutex->unlock();
    }

    return 0;
}

} // namespace obotcha
