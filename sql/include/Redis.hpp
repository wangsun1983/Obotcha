#ifndef __OBOTCHA_REDIS_H__
#define __OBOTCHA_REDIS_H__

#include "Object.hpp"

namespace obotcha {

DECLARE_CLASS(Redis) {
public:
    enum class Event {
        Message = 0,
        Subscribe,
        UnSubscribe,
    };
};

} // namespace obotcha
#endif