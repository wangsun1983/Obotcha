#ifndef __OBOTCHA_STD_INSTANCE_OF_HPP__
#define __OBOTCHA_STD_INSTANCE_OF_HPP__

#include "StrongPointer.hpp"
#include <typeinfo>

namespace obotcha::ostd {

template <typename T, typename U> bool instanceOf(sp<U> a) {
    return typeid(T) == typeid(*a.get_pointer());
}

}; // namespace obotcha

#define IsInstance(PARENT, Y) obotcha::ostd::instanceOf<_##PARENT>(Y)

#endif
