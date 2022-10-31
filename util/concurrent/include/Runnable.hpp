#ifndef __OBOTCHA_RUNNABLE_HPP__
#define __OBOTCHA_RUNNABLE_HPP__

#include <future>
#include <stdio.h>
#include <utility>

#include "OStdApply.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

DECLARE_CLASS(Runnable) {
public:
    virtual void run() = 0;

    virtual bool onInterrupt() { 
        return false;
    }

    virtual ~_Runnable() {}
};

template <class Function, class... Args>
class _LambdaRunnable : public _Runnable {
public:
    _LambdaRunnable(Function &&f, Args &&... args)
        : _Runnable(), func(f), _arguments(std::make_tuple(args...)) {}

    void run() {
        // func(initializer_list(_arguments));
        ostd::apply(func, _arguments);
    }

    ~_LambdaRunnable() {
        // do nothing
    }

private:
    std::tuple<Args...> _arguments;
    Function func;
};

template <typename Callfunc, typename... Args>
sp<_Runnable> createLambdaRunnable(Callfunc f, Args... args) {
    _Runnable *r = new _LambdaRunnable<Callfunc, Args...>(
        std::forward<Callfunc>(f), std::forward<Args>(args)...);
    return AutoClone(r);
}

} // namespace obotcha

#endif