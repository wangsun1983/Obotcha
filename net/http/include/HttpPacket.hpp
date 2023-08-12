#ifndef __OBOTCHA_HTTP_PACKET_HPP__
#define __OBOTCHA_HTTP_PACKET_HPP__

#include "Object.hpp"
#include "HttpHeader.hpp"
#include "HttpEntity.hpp"

namespace obotcha {

DECLARE_CLASS(HttpPacket) {

public:
    friend class _HttpRequestParser;
    friend class _HttpResponseParser;
    friend class _HttpServer;
    friend class _Http2StreamController;

    _HttpPacket() = default;
    
    void setHeader(HttpHeader);
    HttpHeader getHeader();

    HttpEntity getEntity();
    void setEntity(HttpEntity);

    //HttpPacket::Type
    void setType(st(Http)::PacketType);
    st(Http)::PacketType getType() const;

    bool isChunked();
    
    static const int kHttpBufferSize;
private:
    HttpHeader mHeader = createHttpHeader();
    HttpEntity mEntity = createHttpEntity();
    st(Http)::PacketType mType = st(Http)::PacketType::Unknown;
};

}
#endif
