#ifndef __OBOTCHA_HTTP_PACKET_PARSER_HPP__
#define __OBOTCHA_HTTP_PACKET_PARSER_HPP__

#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HashMap.hpp"
#include "ArrayList.hpp"
#include "HttpUrl.hpp"
#include "ByteRingArray.hpp"
#include "ByteRingArrayReader.hpp"
#include "Enviroment.hpp"
#include "HttpPacket.hpp"
#include "HttpMultiPartParser.hpp"
#include "HttpChunkParser.hpp"
#include "HttpHeaderParser.hpp"

namespace obotcha {

DECLARE_CLASS(HttpPacketParser) {

public:
    
    virtual int pushData(ByteArray) = 0;

    virtual ArrayList<HttpPacket> doParse() = 0;

    //virtual HttpPacket parseEntireRequest(ByteArray request) = 0;

    virtual void reset() = 0;

    //int getStatus();
    //void setStatus(int);

//protected:
    //int mStatus;
};

}

#endif
