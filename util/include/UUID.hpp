#ifndef __OBOTCHA_UUID_HPP__
#define __OBOTCHA_UUID_HPP__

#include "uuid.h"

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(UUID) {
public:
    enum Type {
        Random = 0,
        Time,
        TimeSafe,
        Default,
    };

    _UUID();
    _UUID(int);

    String generate();

private:
    int mType;
};

} // namespace obotcha
#endif