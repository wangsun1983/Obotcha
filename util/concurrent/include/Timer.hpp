#ifndef __TIMER_HPP__
#define __TIMER_HPP__

#include <stdio.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "DateTime.hpp"
#include "ScheduledThreadPoolExecutor.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Timer) EXTENDS(Thread) {

public:
    _Timer();

	void schedule(Runnable r,long);

    void schedule(Runnable r,DateTime);

    ~_Timer();

private:
    ScheduledThreadPoolExecutor mScheduledExecutor;
};

}
#endif