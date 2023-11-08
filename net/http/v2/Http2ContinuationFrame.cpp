#include "Http2ContinuationFrame.hpp"

namespace obotcha {

_Http2ContinuationFrame::_Http2ContinuationFrame(HPackDecoder d,HPackEncoder e):_Http2Frame(),encoder(e),decoder(d) {
    type = Type::Continuation;
    headers = createHttpHeader(st(Net)::Protocol::Http_H2);
}

void _Http2ContinuationFrame::load(ByteArray headerBlock) {
    printf("Http2ContinuationFrame load data \n");
    //decoder->decode(this->streamid,headerBlock,headers,true);
    mHeadBlockFragment = headerBlock;
}

ByteArray _Http2ContinuationFrame::getHeadBlockFragment() {
    return mHeadBlockFragment;
}

void _Http2ContinuationFrame::setHeadBlockFragment(ByteArray data) {
    mHeadBlockFragment = data;
}

ByteArray _Http2ContinuationFrame::toByteArray() {
    return mHeadBlockFragment;
}

// void _Http2ContinuationFrame::setHeaders(HttpHeader h) {
//     headers->append(h);
// }

// HttpHeader _Http2ContinuationFrame::getHeaders() {
//     return headers;
// }


}
