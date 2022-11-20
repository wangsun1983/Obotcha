#ifndef __OBOTCHA_WEBSOCKET_OUTPUT_WRITER_HPP__
#define __OBOTCHA_WEBSOCKET_OUTPUT_WRITER_HPP__

#include "Object.hpp"
#include "WebSocketComposer.hpp"
#include "WebSocketProtocol.hpp"
#include "OutputStream.hpp"
#include "Socket.hpp"

namespace obotcha {

DECLARE_CLASS(WebSocketOutputWriter) {
public:
    _WebSocketOutputWriter(int version,int type,Socket sock);

    long sendTextMessage(String);

    long sendBinaryMessage(ByteArray);

    long sendPingMessage(ByteArray);

    long sendPongMessage(ByteArray);

    long sendCloseMessage(int status = st(WebSocketProtocol)::CLOSE_STATUS_NORMAL,
                          ByteArray extraInfo = nullptr);

    void setDeflate(WebSocketPermessageDeflate);

private:
    long send(int type, ByteArray msg);
    WebSocketComposer mComposer;
    Socket mSocket;
    OutputStream mOutputStream;

};

}
#endif
