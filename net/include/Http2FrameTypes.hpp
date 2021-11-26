#ifndef __OBOTCHA_HTTP_V2_FRAME_TYPES_HPP__
#define __OBOTCHA_HTTP_V2_FRAME_TYPES_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

DECLARE_CLASS(Http2FrameTypes) {

public:
    static const int DATA;
    static const int HEADERS;
    static const int PRIORITY;
    static const int RST_STREAM;
    static const int SETTINGS;
    static const int PUSH_PROMISE;
    static const int PING;
    static const int GO_AWAY;
    static const int WINDOW_UPDATE;
    static const int CONTINUATION;
};

}

#endif
