#ifndef __OBOTCHA_WEB_SOCKET_PARSER_HPP__
#define __OBOTCHA_WEB_SOCKET_PARSER_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "WebSocketFrame.hpp"
#include "ByteArrayReader.hpp"
#include "HttpHeader.hpp"
#include "WebSocketPermessageDeflate.hpp"
#include "ByteRingArray.hpp"
#include "ByteRingArrayReader.hpp"

namespace obotcha {


DECLARE_CLASS(WebSocketParser) {
public:
    _WebSocketParser();
    void pushParseData(ByteArray);
    ArrayList<WebSocketFrame> doParse();
    
    virtual bool parseHeader() = 0;
    virtual bool parseContent(bool forceDecompress) = 0;
    virtual bool parsePingBuff() = 0;
    virtual bool parsePongBuff() = 0;
    virtual ByteArray parseContinuationContent(ByteArray) = 0;
    virtual String getOrigin(HttpHeader) = 0;
    virtual int getVersion() = 0;
 
protected:
    enum class Status {
        ParseB0 = 0,
        ParseB1,
        ParseFrameLength,
        ParseMask,
        ParseData
    };

    byte readbyte();
    uint16_t readUint16();
    long readLong();

    bool hasData() const;

    void unMask(byte *payload,const byte *mask,int framezie) const;
    
    ByteArray mContinueBuff = nullptr;
    ByteRingArray mRingBuff = nullptr;
    ByteRingArrayReader mReader = nullptr;
    WebSocketHeader mHeader = nullptr;
    Status mStatus = Status::ParseB0;

    static const int kDefaultBuffSize;
};

}
#endif
