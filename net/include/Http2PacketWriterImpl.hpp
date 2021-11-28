#ifndef __OBOTCHA_HTTP_V2_PACKET_WRITER_IMPL_HPP__
#define __OBOTCHA_HTTP_V2_PACKET_WRITER_IMPL_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "OutputStream.hpp"
#include "ByteArray.hpp"
#include "HttpPacket.hpp"
#include "ByteArray.hpp"
#include "ByteArrayWriter.hpp"
#include "HttpPacketWriter.hpp"

namespace obotcha {

DECLARE_CLASS(Http2PacketWriterImpl) IMPLEMENTS(HttpPacketWriter) {

public:
    _Http2PacketWriterImpl(OutputStream stream,int defaultSize = 1024*32);
    int write(HttpPacket);
    ByteArray data(HttpPacket);

};

}
#endif
