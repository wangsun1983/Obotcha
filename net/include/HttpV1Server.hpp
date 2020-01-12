#ifndef __HTTP_V1_SERVER_HPP__
#define __HTTP_V1_SERVER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "TcpClient.hpp"
#include "HttpUrl.hpp"
#include "TcpServer.hpp"
#include "HttpV1ClientInfo.hpp"
#include "Mutex.hpp"

namespace obotcha {

#define DEFAULT_HTTP_PORT 80

class _HttpV1Server;

DECLARE_SIMPLE_CLASS(HttpV1ClientManager) {
public:
    static sp<_HttpV1ClientManager> getInstance();

    void addClientInfo(int fd,sp<_HttpV1ClientInfo>);

    HttpV1ClientInfo getClientInfo(int fd);

    void removeClientInfo(int fd);
private:
    static Mutex mMutex;

    HashMap<int,HttpV1ClientInfo> mClients;

    static sp<_HttpV1ClientManager> mInstance;

    _HttpV1ClientManager();
};

DECLARE_SIMPLE_CLASS(HttpV1SocketListener) IMPLEMENTS(SocketListener) {
public:
    _HttpV1SocketListener(sp<_HttpV1Server>);

    //implement SocketListener
    void onAccept(int fd,String ip,int port,ByteArray pack);

    void onDisconnect(int fd);

    void onConnect(int fd,String ip,int port);

    void onConnect(int fd,String domain);

    void onTimeout();

private:
    sp<_HttpV1Server> mServer;   
};

DECLARE_SIMPLE_CLASS(HttpListener) {
public:
    void onMessage(int fd,HttpPacket msg);
};

DECLARE_SIMPLE_CLASS(HttpV1Server) IMPLEMENTS(SocketListener){

public:
    friend class _HttpV1SocketListener;
    
    _HttpV1Server(int port,HttpListener);

    _HttpV1Server(HttpListener);

    _HttpV1Server(String ip,int port,HttpListener);

    void parseMessage(int fd,ByteArray);

    bool parseHeader(int fd,ByteArray);

    bool parseBody(int fd,ByteArray);

private:
    TcpServer mTcpServer;

    HttpV1SocketListener mSocketListener;

    HttpListener mHttpListener;

    String mIp;

    int mPort;

    HashMap<int,ByteArray> mBuffPool;

    Mutex mBuffPoolMutex;
};

}
#endif
