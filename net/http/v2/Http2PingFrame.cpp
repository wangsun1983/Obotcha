#include "Http2PingFrame.hpp"
#include "MethodNotSupportException.hpp"
#include "Log.hpp"

namespace obotcha {

_Http2PingFrame::_Http2PingFrame() {
    this->type = TypePing;
}

void _Http2PingFrame::load(ByteArray data) {
    if(data->size() != 8) {
        LOG(ERROR)<<"Ping Frame data is too long";
    }

    info = data;
}

ByteArray _Http2PingFrame::toByteArray() {
    return info;
}

ByteArray _Http2PingFrame::getInfo() {
    return info;
}

void _Http2PingFrame::setInfo(ByteArray s) {
    info = s;
}


}
