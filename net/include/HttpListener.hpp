#ifndef __OBOTCHA_HTTP_LISTENER_HPP__
#define __OBOTCHA_HTTP_LISTENER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "Socket.hpp"
#include "HttpLinker.hpp"
#include "HttpResponseWriter.hpp"
#include "HttpPacket.hpp"
#include "SocketListener.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpListener) {
public:
    enum HttpEvent{    
        Connect = st(SocketListener)::Connect,
        Message = st(SocketListener)::Message,
        Disconnect = st(SocketListener)::Disconnect,
        InternalError = st(SocketListener)::InternalError
    };

    virtual void onHttpMessage(int event,HttpLinker client,HttpResponseWriter w,HttpPacket msg) = 0;
    virtual ~_HttpListener(){}
};

}

#endif