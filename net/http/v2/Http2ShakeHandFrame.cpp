#include "Http2ShakeHandFrame.hpp"
#include "HttpStatus.hpp"
#include "HttpResponse.hpp"
#include "HttpHeaderConnection.hpp"

#include "HttpHeaderUpgrade.hpp"
#include "Log.hpp"

namespace obotcha {

String const _Http2ShakeHandFrame::PreFace = createString("PRI * HTTP/2.0\r\n\r\nSM\r\n\r\n");

_Http2ShakeHandFrame::_Http2ShakeHandFrame(ByteRingArray data) {
    v1Parser = createHttpPacketParserImpl(data);
}

ArrayList<HttpPacket> _Http2ShakeHandFrame::doParser() {
    return v1Parser->doParse();
}

HttpPacket _Http2ShakeHandFrame::toShakeHandPacket(st(Net)::Protocol type) {
    HttpResponse response = createHttpResponse();
    HttpHeader header = response->getHeader();
    header->setResponseStatus(st(HttpStatus)::SwitchProtocls);
    response->getHeader()->setResponseReason(st(HttpStatus)::toString(st(HttpStatus)::SwitchProtocls));

    HttpHeaderConnection c = createHttpHeaderConnection();
    c->set("Upgrade");
    header->setConnection(c);

    HttpHeaderUpgrade upgrade = createHttpHeaderUpgrade();
    switch(type) {
        case st(Net)::Protocol::Http_H2: {
            upgrade->set("h2");
            break;
        }

        case st(Net)::Protocol::Http_H2C:
            upgrade->set("h2c");
        break;

        default:
            LOG(ERROR)<<"Http2ShakeHandFrame toShakeHandPacket unSupport type:"<<static_cast<int>(type);
        break;
    }
    header->setUpgrade(upgrade);
    
    return response;
}

ByteArray _Http2ShakeHandFrame::toPriString() {
    return PreFace->toByteArray();
}

}
