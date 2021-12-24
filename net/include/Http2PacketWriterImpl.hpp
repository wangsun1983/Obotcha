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
#include "Http2StreamController.hpp"

namespace obotcha {

DECLARE_CLASS(Http2PacketWriterImpl) IMPLEMENTS(HttpPacketWriter) {

public:
    _Http2PacketWriterImpl(Http2StreamController);
    int write(HttpPacket);
    ByteArray data(HttpPacket);

private:
    Http2StreamController controller;

};

}
#endif
