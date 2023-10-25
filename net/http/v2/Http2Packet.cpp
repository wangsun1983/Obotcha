#include "Http2Packet.hpp"

namespace obotcha {

_Http2Packet::_Http2Packet(uint32_t streamid,HttpHeader h):streamId(streamid) {
    setHeader(h);
}

_Http2Packet::_Http2Packet(HttpHeader h):_Http2Packet(-1,h) {

}

// ByteArray _Http2Packet::getData() {
//     return data;
// }

// void _Http2Packet::setData(ByteArray d) {
//     data = d;
// }

bool _Http2Packet::isEnd() const {
    return end;
}

void _Http2Packet::setEnd(bool v) {
    end = v;
}

uint32_t _Http2Packet::getStreamId() const {
    return streamId;
}

void _Http2Packet::setStreamId(uint32_t s) {
    streamId = s;
}


}
