#include "Http2Packet.hpp"

namespace obotcha {

_Http2Packet::_Http2Packet(uint32_t streamid,HttpHeader h,ByteArray d) {
    data = d;
    end = false;
    streamId = streamid;
    setHeader(h);
}

ByteArray _Http2Packet::getData() {
    return data;
}

void _Http2Packet::setData(ByteArray d) {
    data = d;
}

bool _Http2Packet::isEnd() {
    return end;
}

void _Http2Packet::setEnd(bool v) {
    end = v;
}

uint32_t _Http2Packet::getStreamId() {
    return streamId;
}

void _Http2Packet::setStreamId(uint32_t s) {
    streamId = s;
}


}
