#ifndef __WEB_SOCKET_PARSER_HPP__
#define __WEB_SOCKET_PARSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketFrame.hpp"
#include "ByteArrayReader.hpp"
#include "HttpHeader.hpp"
#include "WebSocketPermessageDeflate.hpp"

namespace obotcha {


DECLARE_SIMPLE_CLASS(WebSocketParser) {
public:
    void setParseData(ByteArray);
    void setAsClient();

    virtual WebSocketHeader parseHeader() = 0;
    virtual ByteArray parseContent(bool forceDecompress) = 0;
    virtual ByteArray validateContinuationContent(ByteArray) = 0;
    virtual ByteArray parsePingBuff() = 0;
    virtual ByteArray parsePongBuff() = 0;
    virtual String getOrigin(HttpHeader) = 0;
    virtual int getVersion() = 0;
    virtual bool validateHandShake(HttpHeader) = 0;
    virtual bool validateEntirePacket(ByteArray pack) = 0;
    virtual WebSocketPermessageDeflate validateExtensions(HttpHeader) = 0;
    virtual ArrayList<String> extractSubprotocols(HttpHeader) = 0;
 
protected:
    ByteArray mData;
    ByteArrayReader mReader;
    bool isClient;

    WebSocketHeader mHeader;
};

}
#endif
