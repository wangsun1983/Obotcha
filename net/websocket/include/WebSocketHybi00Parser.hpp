#ifndef __OBOTCHA_WEB_SOCKET_HYBI00_PARSER_HPP__
#define __OBOTCHA_WEB_SOCKET_HYBI00_PARSER_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketParser.hpp"

namespace obotcha {

/// Processor for Hybi Draft version 00
/**
 * There are many differences between Hybi 00 and Hybi 13
 */
DECLARE_CLASS(WebSocketHybi00Parser) IMPLEMENTS(WebSocketParser){
public:    
    bool parseHeader() override;

    bool parseContent(bool) override;

    bool parsePingBuff() override;

    bool parsePongBuff() override;

    String getOrigin(HttpHeader) override;

    int getVersion() override;

    ByteArray parseContinuationContent(ByteArray) override;
};

}
#endif
