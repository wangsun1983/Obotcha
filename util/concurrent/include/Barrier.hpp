#ifndef __BARRIER_HPP__
#define __BARRIER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Barrier) {
public:
    _Barrier(int);

    void await(long);

    void await();

    int getWaitNums();

private:
    Mutex mutex;

    Condition cond;

    int mBarrierNums;

    int mBarrierBack;
};

}
#endif