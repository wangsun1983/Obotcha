/**
 * @file CountDownLatch.hpp
 * @brief A synchronization aid that allows one or more threads to wait until
 *        a set of operations being performed in other threads completes.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2022-10-19
 * @license none
 * @history
 */

#ifndef __OBOTCHA_COUNT_DOWN_LATCH_HPP__
#define __OBOTCHA_COUNT_DOWN_LATCH_HPP__

#include "Object.hpp"
#include "Condition.hpp"
#include "Mutex.hpp"
#include "Util.hpp"

namespace obotcha {

DECLARE_CLASS(CountDownLatch) {
  public:
    explicit _CountDownLatch(uint32_t count);

    int countDown();

    int await(long interval = st(Concurrent)::kWaitForEver);

    int getCount();

    int release();

  private:
    uint32_t mCount;
    Condition mWaitCond = createCondition();
    Mutex mWaitMutex = createMutex();
};

} // namespace obotcha
#endif