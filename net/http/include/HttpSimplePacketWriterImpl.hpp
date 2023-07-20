#ifndef __OBOTCHA_HTTP_SIMPLE_PACKET_WRITER_IMPL_HPP__
#define __OBOTCHA_HTTP_SIMPLE_PACKET_WRITER_IMPL_HPP__

#include "Object.hpp"
#include "OutputStream.hpp"
#include "ByteArray.hpp"
#include "HttpPacket.hpp"
#include "HttpPacketWriter.hpp"

namespace obotcha {

//support Http0.9 simple request
DECLARE_CLASS(HttpSimplePacketWriterImpl) IMPLEMENTS(HttpPacketWriter) {

public:
    explicit _HttpSimplePacketWriterImpl(OutputStream stream);
    int write(HttpPacket);
    ByteArray data(HttpPacket);

private:
    OutputStream mStream;
};

}
#endif
