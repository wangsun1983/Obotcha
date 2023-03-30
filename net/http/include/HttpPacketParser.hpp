#ifndef __OBOTCHA_HTTP_PACKET_PARSER_HPP__
#define __OBOTCHA_HTTP_PACKET_PARSER_HPP__

#include "Object.hpp"
#include "HttpPacket.hpp"
#include "ArrayList.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_CLASS(HttpPacketParser) {

public:
    virtual int pushData(ByteArray) = 0;
    virtual ArrayList<HttpPacket> doParse() = 0;
    virtual void reset() = 0;
};

}

#endif
