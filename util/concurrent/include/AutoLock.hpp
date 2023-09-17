/**
 * @file AutoLock.hpp
 * @brief Manages the mutex automatically. It'll be locked when Autolock is
 *        constructed and released when Autolock goes out of scope.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.2
 * @date 2022-10-19
 * @license none
 * @history
 */

#ifndef __OBOTCHA_AUTO_LOCK_HPP__
#define __OBOTCHA_AUTO_LOCK_HPP__

#include "Lock.hpp"

namespace obotcha {

class _Condition;
class _ProcessCondition;

class AutoLock {
public:
    friend class _Condition;
    friend class _ProcessCondition;
    
    explicit AutoLock(Lock lock);

    AutoLock(AutoLock &lock) = delete;
    AutoLock& operator=(const AutoLock& other) = delete;

    ~AutoLock();
    void release();

private:
    Lock mLock;
};

}
#endif
