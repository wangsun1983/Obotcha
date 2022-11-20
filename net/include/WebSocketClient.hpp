#ifndef __OBOTCHA_WEBSOCKET_CLIENT_HPP__
#define __OBOTCHA_WEBSOCKET_CLIENT_HPP__

#include "Object.hpp"
#include "WebSocketListener.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketComposer.hpp"
#include "SocketListener.hpp"
#include "HttpOption.hpp"
#include "SocketMonitor.hpp"
#include "OutputStream.hpp"
#include "WebSocketOutputWriter.hpp"
#include "WebSocketInputReader.hpp"
#include "WebSocketValidator.hpp"
#include "WebSocketInspector.hpp"

namespace obotcha {

DECLARE_CLASS(WebSocketClient) IMPLEMENTS(SocketListener){
public:
    _WebSocketClient(int version = 13);
    
    int connect(String url,WebSocketListener l,HttpOption option = nullptr);

    int sendTextMessage(String msg);

    int sendTextMessage(const char*msg);

    int sendPingMessage(ByteArray msg);

    int sendPongMessage(ByteArray msg);

    int sendCloseMessage(int status = st(WebSocketProtocol)::CLOSE_STATUS_NORMAL,
                          ByteArray extraInfo = nullptr);

    int sendBinaryMessage(ByteArray data);

    int sendFile(File);

    void close();

private:
    void onSocketMessage(int,Socket,ByteArray);

    WebSocketListener mWsListener;
    HttpOption mHttpOption;
    static SocketMonitor mSocketMonitor;
    WebSocketOutputWriter mWriter;
    WebSocketInputReader mReader;
    WebSocketInspector mInspector;
    Socket mSocket;
    int mVersion;
    
};


}
#endif
