#ifndef __COUNT_DOWN_LATCH_HPP__
#define __COUNT_DOWN_LATCH_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "Mutex.hpp"
#include "AutoMutex.hpp"
#include "Condition.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(CountDownLatch) {
public:
    _CountDownLatch(int v);
    
    int countDown();

    void await(long);
    
private:
    int count;
    Mutex mutex;
    Condition waitCond;
    Mutex waitMutex;
};

}
#endif