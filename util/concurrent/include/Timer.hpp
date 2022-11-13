#ifndef __OBOTCHA_TIMER_HPP__
#define __OBOTCHA_TIMER_HPP__

#include "Object.hpp"
#include "DateTime.hpp"
#include "ThreadScheduledPoolExecutor.hpp"

namespace obotcha {

DECLARE_CLASS(Timer) IMPLEMENTS(Thread) {

  public:
    _Timer();

    Future schedule(long, Runnable r);

    Future schedule(DateTime, Runnable r);

    template <class Function, class... Args>
    Future schedule(long delay, Function &&f, Args &&... args) {
        return schedule(delay, createLambdaRunnable(f, args...));
    }

    template <class Function, class... Args>
    Future schedule(DateTime date, Function && f, Args && ... args) {
        return schedule(date, createLambdaRunnable(f, args...));
    }

    ~_Timer();

  private:
    static ThreadScheduledPoolExecutor mScheduledExecutor;
};

} // namespace obotcha
#endif