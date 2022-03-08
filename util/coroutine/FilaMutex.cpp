#include "co_routine_inner.h"
#include "FilaMutex.hpp"
#include "Filament.hpp"

namespace obotcha {

_FilaMutex::_FilaMutex() {
    mMutex = createMutex();
    owner = nullptr;
}

int _FilaMutex::lock() {
    auto coa = GetCurrThreadCo();
    while(1) {
        printf("lock trace1 \n");
        mMutex->lock();
        printf("lock trace2 \n");
        if(owner == nullptr) {
            printf("lock trace3 \n");
            owner = coa;
            //mMutex->unlock();
            printf("lock trace4 \n");
            break;
        }else if(owner == coa) {
            printf("lock trace5 \n");
            //mMutex->unlock();
            printf("lock trace6 \n");
            break;
        }
        mMutex->unlock();
    }

    return 0;
}

int _FilaMutex::unlock() {
    auto coa = GetCurrThreadCo();
    mMutex->lock();
    if(owner == coa) {
        owner = nullptr;
    }
    mMutex->unlock();
    return 0;
}


} // namespace obotcha
