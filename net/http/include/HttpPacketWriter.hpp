#ifndef __OBOTCHA_HTTP_PACKET_WRITER_HPP__
#define __OBOTCHA_HTTP_PACKET_WRITER_HPP__

#include "Object.hpp"
#include "ByteArray.hpp"
#include "HttpPacket.hpp"
#include "ByteArray.hpp"
#include "ByteArrayWriter.hpp"

namespace obotcha {

DECLARE_CLASS(HttpPacketWriter) {

public:
    virtual long write(HttpPacket) = 0;
    virtual ByteArray data(HttpPacket) = 0;
};

using HttpResponseWriter = sp<_HttpPacketWriter>;
using HttpRequestWriter = sp<_HttpPacketWriter>;

}
#endif
