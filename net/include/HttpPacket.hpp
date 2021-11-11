#ifndef __OBOTCHA_HTTP_PACKET_HPP__
#define __OBOTCHA_HTTP_PACKET_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "HttpHeader.hpp"
#include "ByteArray.hpp"
#include "HttpCookie.hpp"

#include "HttpMethod.hpp"
#include "HttpHeaderVersion.hpp"
#include "HttpEntity.hpp"

namespace obotcha {

DECLARE_CLASS(HttpPacket) {

public:
    enum Type {
        Request = 0,
        Response,
    };
    
    friend class _HttpRequestParser;
    friend class _HttpResponseParser;

    _HttpPacket();
    
    void setHeader(HttpHeader);
    HttpHeader getHeader();

    HttpEntity getEntity();
    void setEntity(HttpEntity);

    void setType(int);
    int getType();

private:
    HttpHeader mHeader;
    HttpEntity mEntity;
    int mType;
};

}
#endif
