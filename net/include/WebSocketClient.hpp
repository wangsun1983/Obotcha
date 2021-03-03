#ifndef __OBOTCHA_WEBSOCKET_CLIENT_HPP__
#define __OBOTCHA_WEBSOCKET_CLIENT_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <netinet/in.h>
#include <mqueue.h>
#include <fstream>
#include <sys/un.h>


#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "SocketListener.hpp"
#include "Mutex.hpp"
#include "Pipe.hpp"
#include "Thread.hpp"
#include "WebSocketListener.hpp"
#include "SocketListener.hpp"
#include "EPollFileObserver.hpp"
#include "Mutex.hpp"
#include "HttpResponseParser.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketHybi13Parser.hpp"
#include "WebSocketClientInfo.hpp"
#include "WebSocketComposer.hpp"

namespace obotcha {

enum WsClientProtocolType {
    WsClientProtocolHttp,
    WsClientProtocolWebSocket
};

DECLARE_SIMPLE_CLASS(WebSocketTcpClientListener) IMPLEMENTS(SocketListener) {

public:
    _WebSocketTcpClientListener(WebSocketListener,WebSocketClientInfo);

    void onDataReceived(Socket r,ByteArray pack);

    void onDisconnect(Socket r);

    void onConnect(Socket r);

    void onTimeout();

private:
    WebSocketListener mWsListener;

    WebSocketHybi13Parser mHybi13Parser;

    int mProtoclType;

    HttpResponseParser mHttpParser;

    WebSocketClientInfo mClient;
};

DECLARE_SIMPLE_CLASS(WebSocketClient) {
public:
    _WebSocketClient(int version);

    void setSendTimeout(long);
    long getSendTimeout();

    void setRcvTimeout(long);
    long getRcvTimeout();

    WebSocketClient buildConnectInfo(String header,String value);

    void clearConnectInfo();

    void updateConnectInfo(String header,String value);

    void updateMask(bool);

    int connect(String url,WebSocketListener l);

    int sendTextMessage(String msg);

    int sendTextMessage(const char*msg);

    int sendPingMessage(ByteArray msg);

    int sendCloseMessage(ByteArray msg);

    int sendBinaryData(ByteArray data);

    int sendFile(File);

    WebSocketClientInfo getClientInfo();

private:

    int mVersion;

    //TcpClient mTcpClient;

    WebSocketTcpClientListener mListener;

    WebSocketListener mWsListener;

    bool isConnected;

    //WebSocketFrameComposer mComposer;

    WebSocketClientInfo mClient;

    long mSendTimeout;
    long mRcvTimeout;
};


}
#endif
