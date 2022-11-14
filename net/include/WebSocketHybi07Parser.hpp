#ifndef __OBOTCHA_WEB_SOCKET_HYBI07_PARSER_HPP__
#define __OBOTCHA_WEB_SOCKET_HYBI07_PARSER_HPP__

#include "Object.hpp"
#include "WebSocketHybi08Parser.hpp"

namespace obotcha {

/// Processor for Hybi Draft version 07
/**
 * The primary difference between 07 and 08 is a version number.
 */
DECLARE_CLASS(WebSocketHybi07Parser) IMPLEMENTS(WebSocketHybi08Parser) {

  public:
    int getVersion();
};

} // namespace obotcha
#endif
