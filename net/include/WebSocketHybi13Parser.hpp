#ifndef __OBOTCHA_WEB_SOCKET_HYBI13_PARSER_HPP__
#define __OBOTCHA_WEB_SOCKET_HYBI13_PARSER_HPP__

#include "Object.hpp"
#include "ByteArray.hpp"
#include "String.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketPermessageDeflate.hpp"
#include "ByteRingArray.hpp"
#include "ByteRingArrayReader.hpp"

namespace obotcha {

DECLARE_CLASS(WebSocketHybi13Parser) IMPLEMENTS(WebSocketParser) {
  public:
    _WebSocketHybi13Parser();

    bool parseHeader();

    bool parseContent(bool forceDecompress);

    bool parsePingBuff();

    bool parsePongBuff();

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
