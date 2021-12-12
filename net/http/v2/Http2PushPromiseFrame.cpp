#include "Http2PushPromiseFrame.hpp"

namespace obotcha {

ByteArray _Http2PushPromiseFrame::toByteArray() {
    //TODO
}

void _Http2PushPromiseFrame::import(ByteArray) {
    //TODO
}

void _Http2PushPromiseFrame::setHttpHeaders(HttpHeader h) {
    headers = h;
}

HttpHeader _Http2PushPromiseFrame::getHttpHeaders() {
    return headers;
}

}
