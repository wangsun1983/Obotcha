#ifndef __OBOTCHA_WEB_SOCKET_HYBI08_PARSER_HPP__
#define __OBOTCHA_WEB_SOCKET_HYBI08_PARSER_HPP__

#include "Object.hpp"
#include "WebSocketHybi13Parser.hpp"

namespace obotcha {

/// Processor for Hybi Draft version 08
/**
 * The primary difference between 08 and 13 is a different origin header name
 */
DECLARE_CLASS(WebSocketHybi08Parser) IMPLEMENTS(WebSocketHybi13Parser){
public:
    String getOrigin(HttpHeader h) override;
    
    int getVersion() override;

};

}
#endif
