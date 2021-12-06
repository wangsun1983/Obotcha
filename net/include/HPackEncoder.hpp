#ifndef __OBOTCHA_HPACK_ENCODER_HPP__
#define __OBOTCHA_HPACK_ENCODER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

DECLARE_CLASS(HPackEncoder) {

public:
    _HPackEncoder();

private:

    int mIndex;
};

}

#endif
