#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "HttpClient.hpp"
#include "HttpPacket.hpp"
#include "InetAddress.hpp"
#include "HttpHeader.hpp"
#include "HttpParser.hpp"
#include "ByteArrayReader.hpp"
#include "Error.hpp"
#include "HttpV1Server.hpp"
#include "InitializeException.hpp"

namespace obotcha {

_HttpV1SocketListener::_HttpV1SocketListener(HttpV1Server s) {
    mServer = s;
}

void _HttpV1SocketListener::onAccept(int fd,String ip,int port,ByteArray pack) {
    mServer->parseMessage(fd,pack);
}

void _HttpV1SocketListener::onDisconnect(int fd) {
    //TODO
}

void _HttpV1SocketListener::onConnect(int fd,String ip,int port) {
    //TODO
}

void _HttpV1SocketListener::onConnect(int fd,String domain) {
    //TODO
}

void _HttpV1SocketListener::onTimeout() {
    //TODO
}

_HttpV1Server::_HttpV1Server(int port,HttpListener l) {

}

_HttpV1Server::_HttpV1Server(HttpListener l):_HttpV1Server{nullptr,-1,l} {
    
}

_HttpV1Server::_HttpV1Server(String ip,int port,HttpListener l){
    HttpV1Server server;
    server.set_pointer(this);
    mSocketListener = createHttpV1SocketListener(server);

    mHttpListener = l;

    mIp = ip;
    mPort = port;

    if(mIp == nullptr) {
        mTcpServer = createTcpServer(mPort,mSocketListener);
    } else {
        mTcpServer = createTcpServer(mIp,mPort,mSocketListener);
    }

    mBuff = createByteArray(mTcpServer->getRcvBuffSize());

    if(mTcpServer->start() != 0) {
        throw createInitializeException("tcp server start fail!!");
    }
}

}

