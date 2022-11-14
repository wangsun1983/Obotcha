#ifndef __OBOTCHA_HTTP_LISTENER_HPP__
#define __OBOTCHA_HTTP_LISTENER_HPP__

#include "Object.hpp"
#include "HttpPacketWriter.hpp"
#include "HttpLinker.hpp"

namespace obotcha {

DECLARE_CLASS(HttpListener) {
public:
    virtual void onHttpMessage(int event,HttpLinker client,HttpResponseWriter w,HttpPacket msg) = 0;
    virtual ~_HttpListener(){}
};

}

#endif