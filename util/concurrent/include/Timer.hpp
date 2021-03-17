#ifndef __OBOTCHA_TIMER_HPP__
#define __OBOTCHA_TIMER_HPP__

#include <stdio.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "DateTime.hpp"
#include "ThreadScheduledPoolExecutor.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Timer) IMPLEMENTS(Thread) {

public:
    _Timer();

	void schedule(Runnable r,long);

    void schedule(Runnable r,DateTime);

    ~_Timer();

private:
    ThreadScheduledPoolExecutor mScheduledExecutor;
};

}
#endif