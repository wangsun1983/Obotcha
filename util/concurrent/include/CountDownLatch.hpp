#ifndef __OBOTCHA_COUNT_DOWN_LATCH_HPP__
#define __OBOTCHA_COUNT_DOWN_LATCH_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "Mutex.hpp"
#include "Condition.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(CountDownLatch) {
public:
    _CountDownLatch(int v);
    
    int countDown();

    int await(long);

    int await();
    
private:
    int count;
    Condition waitCond;
    Mutex waitMutex;
};

}
#endif