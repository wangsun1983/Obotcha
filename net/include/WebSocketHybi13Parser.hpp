#ifndef __WEB_SOCKET_HYBI13_PARSER_HPP__
#define __WEB_SOCKET_HYBI13_PARSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketParser.hpp"

namespace obotcha {


DECLARE_SIMPLE_CLASS(WebSocketHybi13Parser) IMPLEMENTS(WebSocketParser){
public:
    WebSocketHeader parseHeader();
    String parseMessage();

};

}
#endif
