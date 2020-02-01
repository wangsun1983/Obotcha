#ifndef __WEBSOCKET_CLIENT_HPP__
#define __WEBSOCKET_CLIENT_HPP__

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
#include "AtomicInteger.hpp"
#include "Thread.hpp"
#include "TcpServer.hpp"
#include "WebSocketListener.hpp"
#include "SocketListener.hpp"
#include "EPollFileObserver.hpp"
#include "Mutex.hpp"
#include "HttpV1Parser.hpp"
//#include "WebSocketFrameComposer.hpp"
#include "WebSocketParser.hpp"
#include "AsyncTcpClient.hpp"
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

    void onAccept(int fd,String ip,int port,ByteArray pack);

    void onDisconnect(int fd);

    void onConnect(int fd,String ip,int port);

    void onConnect(int fd,String domain);

    void onTimeout();

private:
    WebSocketListener mWsListener;

    WebSocketHybi13Parser mHybi13Parser;

    int mProtoclType;

    HttpV1Parser mHttpParser;

    WebSocketClientInfo mClient;
};

DECLARE_SIMPLE_CLASS(WebSocketClient) {
public:
    _WebSocketClient(int version);

    WebSocketClient buildConnectInfo(String header,String value);

    void clearConnectInfo();

    void updateConnectInfo(int header,String value);

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

    AsyncTcpClient mTcpClient;

    WebSocketTcpClientListener mListener;

    WebSocketListener mWsListener;

    bool isConnected;

    //WebSocketFrameComposer mComposer;

    WebSocketClientInfo mClient;
};


}
#endif
