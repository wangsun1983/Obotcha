#include "Http2PacketWriterImpl.hpp"

namespace obotcha {

_Http2PacketWriterImpl::_Http2PacketWriterImpl(Http2StreamController c) {
    controller = c;
}

int _Http2PacketWriterImpl::write(HttpPacket p) {
    Http2Packet packet = Cast<Http2Packet>(p);
    auto stream = controller->newStream();
    return stream->write(packet);
}

ByteArray _Http2PacketWriterImpl::data(HttpPacket) {
    return nullptr;
}

}