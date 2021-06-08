#ifndef __OBOTCHA_WEB_SOCKET_HYBI13_PARSER_HPP__
#define __OBOTCHA_WEB_SOCKET_HYBI13_PARSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketPermessageDeflate.hpp"
#include "ZipMemoryStream.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(WebSocketHybi13Parser) IMPLEMENTS(WebSocketParser) {
public:
    _WebSocketHybi13Parser();
    
    WebSocketHeader parseHeader();

    ByteArray parseContent(bool forceDecompress);

    ByteArray parsePingBuff();

    ByteArray parsePongBuff();

    String getOrigin(HttpHeader);

    int getVersion();

    bool validateHandShake(HttpHeader);

    WebSocketPermessageDeflate validateExtensions(HttpHeader);

    ByteArray validateContinuationContent(ByteArray);

    bool validateEntirePacket(ByteArray pack);

    ArrayList<String> extractSubprotocols(HttpHeader);

private:
    WebSocketPermessageDeflate mDeflate;  
};

}
#endif
