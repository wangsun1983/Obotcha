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

namespace obotcha {

DECLARE_CLASS(Barrier) {
  public:
    _Barrier(int nums);

    int await(long interval = 0);

    using __WaitAction = std::function<void()>;
    int await(__WaitAction func,long interval = 0) {
        int result = 0;

        AutoLock l(mutex);
        mBarrierNums--;
        if(mBarrierNums == 0) {
            cond->notifyAll();
        } else if(mBarrierNums > 0) {
            result = cond->wait(mutex, interval);
        }

        if(mBarrierNums == 0 && func != nullptr) {
            func();
        }
        
        return result;
    }

    int getWaitNums();

    int release();

  private:
    Mutex mutex;

    Condition cond;

    int mBarrierNums;
};

} // namespace obotcha
#endif
