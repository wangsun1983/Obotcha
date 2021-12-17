#ifndef __OBOTCHA_HTTP_V2_LISTENER_HPP__
#define __OBOTCHA_HTTP_V2_LISTENER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "Socket.hpp"
#include "HttpLinker.hpp"
#include "HttpPacket.hpp"
#include "SocketListener.hpp"
#include "Http2ResponseWriter.hpp"
#include "Http2Packet.hpp"

namespace obotcha {

DECLARE_CLASS(Http2Listener) {
public:
    virtual void onHttpMessage(int event,HttpLinker client,Http2ResponseWriter w,Http2Packet msg) = 0;
    virtual ~_Http2Listener(){}
};

}

#endif