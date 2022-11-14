#ifndef __OBOTCHA_WEB_SOCKET_HYBI13_PARSER_HPP__
#define __OBOTCHA_WEB_SOCKET_HYBI13_PARSER_HPP__

#include "Object.hpp"
#include "ByteArray.hpp"
#include "String.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketPermessageDeflate.hpp"

namespace obotcha {

DECLARE_CLASS(WebSocketHybi13Parser) IMPLEMENTS(WebSocketParser) {
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

} // namespace obotcha
#endif
