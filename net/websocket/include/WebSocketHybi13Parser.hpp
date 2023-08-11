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

    bool parseHeader() override;

    bool parseContent(bool forceDecompress) override;

    bool parsePingBuff() override;

    bool parsePongBuff() override;

    String getOrigin(HttpHeader) override;

    int getVersion() override;

    ByteArray parseContinuationContent(ByteArray) override;

  private:
    WebSocketPermessageDeflate mDeflate;
};

} // namespace obotcha
#endif
