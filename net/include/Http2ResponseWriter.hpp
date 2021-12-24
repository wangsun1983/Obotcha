#ifndef __OBOTCHA_HTTP_V2_RESPONSE_WRITER_HPP__
#define __OBOTCHA_HTTP_V2_RESPONSE_WRITER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "Socket.hpp"
#include "HttpLinker.hpp"
#include "HttpPacket.hpp"
#include "SocketListener.hpp"
#include "HttpPacketWriter.hpp"
#include "Http2Frame.hpp"

namespace obotcha {

DECLARE_CLASS(Http2ResponseWriter) IMPLEMENTS(HttpPacketWriter){
public:
    _Http2ResponseWriter(Http2Stream);
    int write(HttpPacket);
    ByteArray data(HttpPacket);

private:
    Http2Stream stream;
};

}

#endif