#ifndef __OBOTCHA_DEFER_HPP__
#define __OBOTCHA_DEFER_HPP__

#include <functional>

namespace obotcha {

class Defer {
public:
    Defer(std::function<void()> func) {
        mDeferFunction = func;
    }

    ~Defer() {
        mDeferFunction();
    }

private:
    std::function<void()> mDeferFunction;
};

} // namespace obotcha
#endif