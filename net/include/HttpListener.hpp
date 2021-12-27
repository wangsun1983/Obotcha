#ifndef __OBOTCHA_HTTP_LISTENER_HPP__
#define __OBOTCHA_HTTP_LISTENER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "Socket.hpp"
#include "HttpLinker.hpp"
#include "HttpPacket.hpp"
#include "SocketListener.hpp"
#include "HttpPacketWriter.hpp"

namespace obotcha {

DECLARE_CLASS(HttpListener) {
public:
    virtual void onHttpMessage(int event,HttpLinker client,HttpResponseWriter w,HttpPacket msg) = 0;
    virtual ~_HttpListener(){}
};

}

#endif