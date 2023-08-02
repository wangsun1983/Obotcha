#ifndef __OBOTCHA_HTTP_PACKET_WRITER_IMPL_HPP__
#define __OBOTCHA_HTTP_PACKET_WRITER_IMPL_HPP__

#include "Object.hpp"
#include "OutputStream.hpp"
#include "ByteArray.hpp"
#include "HttpPacket.hpp"
#include "ByteArray.hpp"
#include "ByteArrayWriter.hpp"
#include "HttpPacketWriter.hpp"

namespace obotcha {

DECLARE_CLASS(HttpPacketWriterImpl) IMPLEMENTS(HttpPacketWriter) {

public:
    _HttpPacketWriterImpl(OutputStream stream,int defaultSize = 1024*32);
    long write(HttpPacket);
    ByteArray data(HttpPacket);

private:
    int mDefaultSize;
    ByteArray mBuff;
    ByteArrayWriter mWriter;
    OutputStream mStream;

    int computeContentLength(HttpPacket) const;
    int flush(HttpPacket packet,bool send);
    int write(ByteArray,bool send);

    void updateHttpHeader(HttpPacket packet);
};

}
#endif
