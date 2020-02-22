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
#include "SocketListener.hpp"
#include "HttpV1ResponseWriter.hpp"
#include "HttpMultiPart.hpp"

namespace obotcha {

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

DECLARE_SIMPLE_CLASS(HttpV1Listener) {
public:
    virtual void onMessage(HttpV1ClientInfo client,HttpV1ResponseWriter w,HttpPacket msg) = 0;
    virtual void onConnect(HttpV1ClientInfo) = 0;
    virtual void onDisconnect(HttpV1ClientInfo) = 0;
};

DECLARE_SIMPLE_CLASS(HttpV1Server) {

public:
    friend class _HttpV1SocketListener;
    
    _HttpV1Server(int port,HttpV1Listener);

    _HttpV1Server(HttpV1Listener);

    _HttpV1Server(String ip,int port,HttpV1Listener);

    void parseMessage(int fd,ByteArray);

    void addClient(int fd);

    void removeClient(int fd);

    void exit();

private:
    TcpServer mTcpServer;

    HttpV1SocketListener mSocketListener;

    HttpV1Listener mHttpListener;

    String mIp;

    int mPort;

    HashMap<int,ByteArray> mBuffPool;

    Mutex mBuffPoolMutex;
};

}
#endif
