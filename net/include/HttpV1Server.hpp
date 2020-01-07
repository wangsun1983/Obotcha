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

namespace obotcha {

#define DEFAULT_HTTP_PORT 80

class _HttpV1Server;

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
    _HttpV1Server(int port,HttpListener);

    _HttpV1Server(HttpListener);

    _HttpV1Server(String ip,int port,HttpListener);

    void parseMessage(int fd,ByteArray);

private:
    TcpServer mTcpServer;

    HttpV1SocketListener mSocketListener;

    HttpListener mHttpListener;

    ByteArray mBuff;

    String mIp;

    int mPort;
};

}
#endif
