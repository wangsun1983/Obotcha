#ifndef __OBOTCHA_HTTP_V2_STEAM_ID_HPP__
#define __OBOTCHA_HTTP_V2_STEAM_ID_HPP__

#include <atomic>

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

DECLARE_CLASS(Http2StreamId) {

public:
    _Http2StreamId(bool isServer);
    int next();

private:
    std::atomic_int id;
};

}

#endif
