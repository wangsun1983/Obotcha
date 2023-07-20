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
    ~AutoLock();
    void release();

private:
    Lock mLock;
};

}
#endif
