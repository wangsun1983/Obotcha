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
    int write(HttpPacket);
    ByteArray data(HttpPacket);
private:

    int mDefaultSize;
    ByteArray mBuff;
    ByteArrayWriter mWriter;
    OutputStream mStream;

    int _computeContentLength(HttpPacket);
    int _flush(HttpPacket packet,bool send);
    int _write(ByteArray,bool send);
    int _finishWrite();

    int _flushRequest(HttpPacket packet,bool send);
    int _flushResponse(HttpPacket packet,bool send);

    void _updateHttpHeader(HttpPacket packet);
};

}
#endif
