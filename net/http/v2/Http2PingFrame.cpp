#include "Http2PingFrame.hpp"
#include "MethodNotSupportException.hpp"

namespace obotcha {

void _Http2PingFrame::import(ByteArray data) {
    Trigger(MethodNotSupportException,"no ping data");
}

ByteArray _Http2PingFrame::toByteArray() {
    return nullptr;
}

bool _Http2PingFrame::isAck() {
    return ack;
}

void _Http2PingFrame::setAck(bool s) {
    ack = s;
}


}
