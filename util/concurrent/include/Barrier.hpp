#ifndef __OBOTCHA_BARRIER_HPP__
#define __OBOTCHA_BARRIER_HPP__

#include "Condition.hpp"
#include "Mutex.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

DECLARE_CLASS(Barrier) {
  public:
    _Barrier(int);

    int await(long);

    int await();

    int getWaitNums();

    int release();

  private:
    Mutex mutex;

    Condition cond;

    int mBarrierNums;
};

} // namespace obotcha
#endif