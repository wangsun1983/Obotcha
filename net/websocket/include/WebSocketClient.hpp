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
    explicit _WebSocketClient(int version = 13);
    ~_WebSocketClient() override;
    
    int connect(String url,WebSocketListener l,HttpOption option = nullptr);

    long sendTextMessage(String msg);

    long sendTextMessage(const char*msg);

    long sendPingMessage(ByteArray msg);

    long sendPongMessage(ByteArray msg);

    long sendCloseMessage(int status = st(WebSocketProtocol)::CLOSE_STATUS_NORMAL,
                          ByteArray extraInfo = nullptr);

    long sendBinaryMessage(ByteArray data);

    long sendFile(File);

    void close();

private:
    void onSocketMessage(st(Net)::Event,Socket,ByteArray) override;

    static SocketMonitor mSocketMonitor;
    WebSocketListener mWsListener = nullptr;
    HttpOption mHttpOption = nullptr;
    WebSocketOutputWriter mWriter = nullptr;
    WebSocketInputReader mReader = nullptr;
    WebSocketInspector mInspector = nullptr;
    Mutex mMutex = Mutex::New();

    Socket mSocket;
    bool isConnected = false;
    int mVersion;
};


}
#endif
