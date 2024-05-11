#include "Http2ShakeHandFrame.hpp"
#include "HttpStatus.hpp"
#include "HttpResponse.hpp"
#include "HttpHeaderConnection.hpp"

#include "HttpHeaderUpgrade.hpp"
#include "Log.hpp"

namespace obotcha {

String const _Http2ShakeHandFrame::PreFace = String::New("PRI * HTTP/2.0\r\n\r\nSM\r\n\r\n");

_Http2ShakeHandFrame::_Http2ShakeHandFrame(ByteRingArray data) {
    v1Parser = HttpPacketParserImpl::New(data);
}

ArrayList<HttpPacket> _Http2ShakeHandFrame::doParser() {
    return v1Parser->doParse();
}

HttpPacket _Http2ShakeHandFrame::toShakeHandPacket(st(Net)::Protocol type) const {
    HttpResponse response = HttpResponse::New();
    HttpHeader header = response->getHeader();
    header->setResponseStatus(st(HttpStatus)::SwitchProtocls);
    response->getHeader()->setResponseReason(st(HttpStatus)::toString(st(HttpStatus)::SwitchProtocls));

    HttpHeaderConnection c = HttpHeaderConnection::New();
    c->set("Upgrade");
    header->setConnection(c);

    HttpHeaderUpgrade upgrade = HttpHeaderUpgrade::New();
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

ByteArray _Http2ShakeHandFrame::toPriString() const {
    return PreFace->toByteArray();
}

}
