#ifndef __OBOTCHA_WEB_SOCKET_BUFFER_HPP__
#define __OBOTCHA_WEB_SOCKET_BUFFER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ByteArray.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(WebSocketBuffer) {
public:
    ByteArray mBuffer;
    uint64_t clientId;
};

/*
DECLARE_SIMPLE_CLASS(WebSocketContinueBuffer) {
public:
    ByteArray mBuffer;
    //int mType;
    uint64_t clientId;
};

DECLARE_SIMPLE_CLASS(WebSocketEntireBuffer) {
public:
    ByteArray mBuffer;
    uint64_t clientId;
};
*/

}
#endif
