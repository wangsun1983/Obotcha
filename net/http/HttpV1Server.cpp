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
#include "ByteArrayReader.hpp"
#include "Error.hpp"
#include "HttpV1Server.hpp"
#include "InitializeException.hpp"
#include "AutoMutex.hpp"
#include "HttpV1ClientInfo.hpp"
#include "HttpClientManager.hpp"

namespace obotcha {

_HttpV1SocketListener::_HttpV1SocketListener(HttpV1Server s) {
    mServer = s;
}

void _HttpV1SocketListener::onAccept(int fd,String ip,int port,ByteArray pack) {
    printf("_HttpV1SocketListener onAccept,msg is %s \n",pack->toString()->toChars());
    mServer->parseMessage(fd,pack);
}

void _HttpV1SocketListener::onDisconnect(int fd) {
    mServer->removeClient(fd);
}

void _HttpV1SocketListener::onConnect(int fd,String ip,int port) {
    printf("_HttpV1SocketListener onConnect \n");
    HttpV1ClientInfo info = createHttpV1ClientInfo();
    info->setClientFd(fd);
    
    st(HttpV1ClientManager)::getInstance()->addClientInfo(fd,info);
}

void _HttpV1SocketListener::onConnect(int fd,String domain) {
    //Unused
}

void _HttpV1SocketListener::onTimeout() {
    //Unused
}

_HttpV1Server::_HttpV1Server(int port,HttpV1Listener l):_HttpV1Server{nullptr,port,l} {

}

_HttpV1Server::_HttpV1Server(HttpV1Listener l):_HttpV1Server{nullptr,-1,l} {
    
}

_HttpV1Server::_HttpV1Server(String ip,int port,HttpV1Listener l){
    printf("_HttpV1Server start \n");
    HttpV1Server server;
    server.set_pointer(this);
    mSocketListener = createHttpV1SocketListener(server);
    printf("_HttpV1Server trace1 \n");
    mHttpListener = l;

    printf("_HttpV1Server trace1,port is %d \n",port);

    mIp = ip;
    mPort = port;

    if(mIp == nullptr) {
        mTcpServer = createTcpServer(mPort,mSocketListener);
    } else {
        mTcpServer = createTcpServer(mIp,mPort,mSocketListener);
    }

    if(mTcpServer->start() != 0) {
        throw InitializeException("tcp server start fail!!");
    }

    mBuffPoolMutex = createMutex("HttpV1Server mutex");
    mBuffPool = createHashMap<int,ByteArray>();
}

void _HttpV1Server::parseMessage(int fd,ByteArray pack) {
    HttpV1ClientInfo info = st(HttpV1ClientManager)::getInstance()->getClientInfo(fd);
    info->pushHttpData(pack);
    ArrayList<HttpPacket> packets = info->pollHttpPacket();
    printf("parseMessage start \n");
    if(packets != nullptr && packets->size() != 0) {
        ListIterator<HttpPacket> iterator = packets->getIterator();
        while(iterator->hasValue()) {
            printf("parseMessage hit \n");
            //we should check whether there is a multipart
            HttpV1ResponseWriter writer = createHttpV1ResponseWriter(info);
            mHttpListener->onMessage(info,writer,iterator->getValue());
            iterator->next();
        }
    }
}

void _HttpV1Server::addClient(int fd) {
    HttpV1ClientInfo info = st(HttpV1ClientManager)::getInstance()->getClientInfo(fd);
    mHttpListener->onConnect(info);
}

void _HttpV1Server::removeClient(int fd) {
   HttpV1ClientInfo info = st(HttpV1ClientManager)::getInstance()->removeClientInfo(fd);
   mHttpListener->onDisconnect(info);
}

void _HttpV1Server::exit() {
    //TODO
    mTcpServer->release();
    st(HttpV1ClientManager)::getInstance()->clear();
}

}

