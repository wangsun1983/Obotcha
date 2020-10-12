#ifndef __OBOTCHA_BARRIER_HPP__
#define __OBOTCHA_BARRIER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Barrier) {
public:
    _Barrier(int);

    int await(long);

    int await();

    int getWaitNums();

private:
    Mutex mutex;

    Condition cond;

    int mBarrierNums;

    int mBarrierBack;
};

}
#endif