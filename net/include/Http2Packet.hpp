#ifndef __OBOTCHA_HTTP_V2_PACKET_HPP__
#define __OBOTCHA_HTTP_V2_PACKET_HPP__

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
#include "Http2Frame.hpp"
#include "HttpPacket.hpp"

namespace obotcha {

DECLARE_CLASS(Http2Packet) IMPLEMENTS(HttpPacket) {

public:
    _Http2Packet(uint32_t streamid,HttpHeader = nullptr,ByteArray = nullptr);

    ByteArray getData();
    void setData(ByteArray);

    bool isEnd();
    void setEnd(bool);

    uint32_t getStreamId();
    void setStreamId(uint32_t);

private:
    ByteArray data;
    bool end;
    uint32_t streamId;
};

}
#endif
