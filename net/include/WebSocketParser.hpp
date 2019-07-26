#ifndef __WEB_SOCKET_PARSER_HPP__
#define __WEB_SOCKET_PARSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketFrame.hpp"
#include "ByteArrayReader.hpp"

namespace obotcha {


DECLARE_SIMPLE_CLASS(WebSocketParser) {
public:
    void setParseData(ByteArray);
    void setAsClient();

    virtual WebSocketHeader parseHeader() = 0;
    virtual String parseMessage() = 0;
 
protected:
    ByteArray mData;
    ByteArrayReader mReader;
    bool isClient;

    WebSocketHeader mHeader;
};

}
#endif
