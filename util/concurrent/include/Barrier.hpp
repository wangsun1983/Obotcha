/**
 * @file Barrier.hpp
 * @brief A barrier enables multiple threads to synchronize the beginning 
 *        of some computation.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.2
 * @date 2022-10-19
 * @license none
 * @history
 * 1.2022-10-19: Add lambda function for await
 */

#ifndef __OBOTCHA_BARRIER_HPP__
#define __OBOTCHA_BARRIER_HPP__

#include "Condition.hpp"
#include "Mutex.hpp"
#include "Util.hpp"

namespace obotcha {

DECLARE_CLASS(Barrier) {
  public:
    explicit _Barrier(int nums);

    int await(long interval = st(Concurrent)::kWaitForEver);

    int await(const std::function<void()> &func,long interval = st(Concurrent)::kWaitForEver);

    int getWaitNums();

    int release();

  private:
    Mutex mMutex = Mutex::New();

    Condition mCond = Condition::New();

    int mBarrierNums;
};

} // namespace obotcha
#endif
