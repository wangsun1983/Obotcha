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
#include "HttpParser.hpp"
//#include "WebSocketFrameComposer.hpp"
#include "WebSocketParser.hpp"
#include "AsyncTcpClient.hpp"
#include "WebSocketHybi13Parser.hpp"
#include "HttpHeaderParser.hpp"
#include "WebSocketClientInfo.hpp"
#include "WebSocketComposer.hpp"

namespace obotcha {

enum WsClientProtocolType {
    WsClientProtocolHttp,
    WsClientProtocolWebSocket
};

DECLARE_SIMPLE_CLASS(WebSocketTcpClientListener) IMPLEMENTS(SocketListener) {

public:
    _WebSocketTcpClientListener(WebSocketListener);

    void onAccept(int fd,String ip,int port,ByteArray pack);

    void onDisconnect(int fd);

    void onConnect(int fd,String ip,int port);

    void onConnect(int fd,String domain);

    void onTimeout();

private:
    WebSocketListener mWsListener;

    WebSocketHybi13Parser mHybi13Parser;

    int mProtoclType;

    HttpParser mHttpParser;
};

DECLARE_SIMPLE_CLASS(WebSocketClient) {
public:
    _WebSocketClient(int version);

    WebSocketClient buildConnectInfo(int header,String value);

    void clearConnectInfo();

    void updateConnectInfo(int header,String value);

    int connect(String url,WebSocketListener l);

    int sendMessage(String msg);

    int sendMessage(const char*msg);

    int sendByteArray(ByteArray);

    int sendFile(File);

    int sendPing(String msg);

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
