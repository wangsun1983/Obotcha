#include "Http2PacketWriterImpl.hpp"

namespace obotcha {

_Http2PacketWriterImpl::_Http2PacketWriterImpl(OutputStream stream,int defaultSize) {

}
    

int _Http2PacketWriterImpl::write(HttpPacket) {

    return 0;
}

ByteArray _Http2PacketWriterImpl::data(HttpPacket) {
    return nullptr;
}

}