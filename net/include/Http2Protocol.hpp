#ifndef __OBOTCHA_HTTP_V2_PROTOCOL_HPP__
#define __OBOTCHA_HTTP_V2_PROTOCOL_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(Http2Protocol) {

public:
    static const String ConnectionPreface;
};

}

#endif
