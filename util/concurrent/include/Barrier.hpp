#ifndef __OBOTCHA_BARRIER_HPP__
#define __OBOTCHA_BARRIER_HPP__

#include "Condition.hpp"
#include "Mutex.hpp"

namespace obotcha {

DECLARE_CLASS(Barrier) {
  public:
    _Barrier(int nums);

    int await(long interval);

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
