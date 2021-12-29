#include "Http2ContinuationFrame.hpp"

namespace obotcha {

_Http2ContinuationFrame::_Http2ContinuationFrame(HPackDecoder d,HPackEncoder e):_Http2Frame() {
    encoder = e;
    decoder = d;
    type = TypeContinuation;
    headers = createHttpHeader(st(HttpProtocol)::Http_H2);
}

void _Http2ContinuationFrame::import(ByteArray headerBlock) {
    decoder->decode(this->streamid,headerBlock,headers,true);
}

ByteArray _Http2ContinuationFrame::toByteArray() {
    ByteArray data = createByteArray(4*1024);
    ByteArrayWriter writer = createByteArrayWriter(data);
    encoder->encodeHeaders(streamid,writer,headers);
    return data;
}

void _Http2ContinuationFrame::setHeaders(HttpHeader h) {
    headers->addHttpHeader(h);
}

HttpHeader _Http2ContinuationFrame::getHeaders() {
    return headers;
}


}
