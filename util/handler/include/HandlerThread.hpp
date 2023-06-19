#ifndef __OBOTCHA_HANDLER_THREAD_HPP__
#define __OBOTCHA_HANDLER_THREAD_HPP__

#include "Object.hpp"
#include "Looper.hpp"
#include "Thread.hpp"

namespace obotcha {

DECLARE_CLASS(HandlerThread) IMPLEMENTS(Thread) {
public:
    _HandlerThread();
    void run();
    void quit();

    Looper getLooper();

private:
    Looper mLooper;
};

} // namespace obotcha
#endif