#ifndef __OBOTCHA_CLOSE_ABLE_HPP__
#define __OBOTCHA_CLOSE_ABLE_HPP__

#include "Object.hpp"

namespace obotcha {

DECLARE_CLASS(Closeable) {

public:
    virtual void close() = 0;
};

} // namespace obotcha
#endif
