#ifndef __OBOTCHA_COUNT_DOWN_LATCH_HPP__
#define __OBOTCHA_COUNT_DOWN_LATCH_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "Condition.hpp"
#include "Mutex.hpp"

namespace obotcha {

DECLARE_CLASS(CountDownLatch) {
  public:
    _CountDownLatch(int v);

    int countDown();

    int await(long interval = 0);

    int getCount();

    int release();

  private:
    int count;
    Condition waitCond;
    Mutex waitMutex;
};

} // namespace obotcha
#endif