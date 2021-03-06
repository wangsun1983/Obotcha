#ifndef __OBOTCHA_HTTP_LISTENER_HPP__
#define __OBOTCHA_HTTP_LISTENER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "Socket.hpp"
#include "HttpClientInfo.hpp"
#include "HttpResponseWriter.hpp"
#include "HttpPacket.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpListener) {
public:
    enum HttpEvent {
        Connect = st(Socket)::Connect,
        Message = st(Socket)::Message,
        Disconnect = st(Socket)::Disconnect,
    };
    
    virtual void onHttpMessage(int event,HttpClientInfo client,HttpResponseWriter w,HttpPacket msg) = 0;
    virtual ~_HttpListener(){}
};

}

#endif