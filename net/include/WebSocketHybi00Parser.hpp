#ifndef __OBOTCHA_WEB_SOCKET_HYBI00_PARSER_HPP__
#define __OBOTCHA_WEB_SOCKET_HYBI00_PARSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketParser.hpp"

namespace obotcha {

/// Processor for Hybi Draft version 00
/**
 * There are many differences between Hybi 00 and Hybi 13
 */
DECLARE_SIMPLE_CLASS(WebSocketHybi00Parser) IMPLEMENTS(WebSocketParser){
public:    
    WebSocketHeader parseHeader();

    ByteArray parseContent(bool);

    ByteArray parsePingBuff();

    ByteArray parsePongBuff();

    String getOrigin(HttpHeader);

    int getVersion();

    bool validateHandShake(HttpHeader);

    ByteArray validateContinuationContent(ByteArray);

    bool validateEntirePacket(ByteArray pack);

    WebSocketPermessageDeflate validateExtensions(HttpHeader);

    ArrayList<String> extractSubprotocols(HttpHeader);
};

}
#endif
