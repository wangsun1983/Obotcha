#ifndef __OBOTCHA_WEBSOCKET_INPUT_READER_HPP__
#define __OBOTCHA_WEBSOCKET_INPUT_READER_HPP__

#include "Object.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketFrame.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketProtocol.hpp"

namespace obotcha {

DECLARE_CLASS(WebSocketInputReader) {
public:
    _WebSocketInputReader(int version,_WebSocketProtocol::Model model);

    void push(ByteArray data);
    ArrayList<WebSocketFrame> pull();

    WebSocketParser getParser();
private:
    WebSocketParser mParser;

};

}
#endif
