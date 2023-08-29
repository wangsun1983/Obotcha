#ifndef __OBOTCHA_UTIL_HPP__
#define __OBOTCHA_UTIL_HPP__

#include "Object.hpp"

namespace obotcha {

DECLARE_CLASS(Util) {
public:
    class Foreach {
        public:
            enum class Result {
                Continue = 0,
                Break
            };
    };

};

} // namespace obotcha
#endif