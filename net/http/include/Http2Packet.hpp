#ifndef __OBOTCHA_HTTP_V2_PACKET_HPP__
#define __OBOTCHA_HTTP_V2_PACKET_HPP__

#include "Object.hpp"
#include "HttpHeader.hpp"
#include "ByteArray.hpp"
#include "HttpPacket.hpp"

namespace obotcha {

DECLARE_CLASS(Http2Packet) IMPLEMENTS(HttpPacket) {

public:
    _Http2Packet(uint32_t streamid,HttpHeader = nullptr);
    _Http2Packet(HttpHeader = nullptr);
    
    //ByteArray getData();
    //void setData(ByteArray);

    bool isEnd() const;
    void setEnd(bool);

    uint32_t getStreamId() const;
    void setStreamId(uint32_t);

private:
    //ByteArray data;
    bool end = false;
    uint32_t streamId;
};

}
#endif
