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
    //virtual bool validateHandShake(HttpHeader) = 0;
    //virtual bool validateEntirePacket(ByteArray pack) = 0;
    //virtual WebSocketPermessageDeflate validateExtensions(HttpHeader) = 0;
    //virtual ArrayList<String> extractSubprotocols(HttpHeader) = 0;
 
protected:
    enum ParseStatus {
        ParseB0B1 = 0,
        ParseFrameLength,
        ParseMask,
        ParseData
    };

    byte readbyte();
    short int readShortInt();
    long readLong();

    void unMask(byte *payload,byte *mask,int framezie);
    
    ByteArray mContinueBuff;

    //ByteArrayReader mReader;
    ByteRingArray mRingBuff;
    ByteRingArrayReader mReader;

    WebSocketHeader mHeader;
    ByteArray mParseData;
    int mStatus;
};

}
#endif
