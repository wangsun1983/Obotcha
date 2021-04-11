#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "HttpPacket.hpp"
#include "InetAddress.hpp"
#include "HttpHeader.hpp"
#include "Error.hpp"
#include "HttpServer.hpp"
#include "AutoLock.hpp"
#include "HttpClientInfo.hpp"
#include "HttpResponseWriter.hpp"
#include "HttpClientManager.hpp"
#include "SSLManager.hpp"
#include "InterruptedException.hpp"
#include "HttpInternalException.hpp"
#include "SocketBuilder.hpp"
#include "SocketOption.hpp"
#include "Log.hpp"

namespace obotcha {

void _HttpServer::onSocketMessage(int event,Socket r,ByteArray pack) {
    switch(event) {
        case SocketEvent::Message: {
            HttpClientInfo info = st(HttpClientManager)::getInstance()->getClientInfo(r);
            if(info == nullptr) {
                return;
            }
            if(info->pushHttpData(pack) == -1) {
                //some thing may be wrong
                mHttpListener->onHttpMessage(SocketEvent::InternalError,info,nullptr,nullptr);
                st(HttpClientManager)::getInstance()->removeClientInfo(r);
                r->close();
                return;
            }
            
            ArrayList<HttpPacket> packets = info->pollHttpPacket();
            if(packets != nullptr && packets->size() != 0) {
                HttpResponseWriter writer = createHttpResponseWriter(info);
                ListIterator<HttpPacket> iterator = packets->getIterator();
                while(iterator->hasValue()) {
                    mHttpListener->onHttpMessage(event,info,writer,iterator->getValue());
                    iterator->next();
                }
            }
        }
        break;

        case SocketEvent::Connect:{
            HttpClientInfo info = createHttpClientInfo(r);

            SSLInfo ssl = st(SSLManager)::getInstance()->get(r->getFd());
            if(info != nullptr) {
                info->setSSLInfo(ssl);
            }
            st(HttpClientManager)::getInstance()->addClientInfo(info);
            mHttpListener->onHttpMessage(event,info,nullptr,nullptr);
        }
        break;

        case SocketEvent::Disconnect: {
            HttpClientInfo info = st(HttpClientManager)::getInstance()->getClientInfo(r);
            mHttpListener->onHttpMessage(event,info,nullptr,nullptr);
            st(HttpClientManager)::getInstance()->removeClientInfo(r);
        }
    }
}

_HttpServer::_HttpServer(InetAddress addr,HttpListener l,HttpOption option) {
    mHttpListener = l;
    mServerSock = nullptr;
    mSockMonitor = nullptr;
    mSSLServer = nullptr;
    mAddress = addr;
    mOption = option;
}

void _HttpServer::start() {
    String certificate = nullptr; 
    String key = nullptr;
    int sendtimeout = -1;
    int rcvtimeout= -1;

    if(mOption != nullptr) {
        certificate = mOption->getCertificate();
        key = mOption->getKey();
        sendtimeout = mOption->getSendTimeout();
        rcvtimeout = mOption->getRcvTimeout();
    }

    if(certificate != nullptr && key != nullptr) {
        //https server
        mSSLServer = createSSLServer(mAddress->getAddress(),mAddress->getPort(),AutoClone(this),certificate,key);
    } else {
        SocketOption option = createSocketOption();
        
        if(sendtimeout != -1) {
            option->setSendTimeout(sendtimeout);
        }

        if(rcvtimeout != -1) {
            option->setRecvTimeout(rcvtimeout);
        }
        mServerSock = createSocketBuilder()
                        ->setAddress(mAddress)
                        ->newServerSocket();

        mServerSock->bind();
        int threadsNum = st(Enviroment)::getInstance()->getInt(st(Enviroment)::gHttpServerThreadsNum,4);
        mSockMonitor = createSocketMonitor(threadsNum);
        mSockMonitor->bind(mServerSock,AutoClone(this));
    }
}

//interface for websocket
void _HttpServer::deMonitor(Socket s) {
    mSockMonitor->remove(s);
}

void _HttpServer::exit() {
    if(mSockMonitor != nullptr) {
        mSockMonitor->release();
        mSockMonitor = nullptr;
    }

    if(mServerSock != nullptr) {
        mServerSock->close();
        mServerSock = nullptr;
    }

    if(mSSLServer != nullptr) {
        mSSLServer->release();
        mSSLServer = nullptr;
    }

    st(HttpClientManager)::getInstance()->clear();
}

_HttpServer::~_HttpServer() {
    if(mSockMonitor != nullptr) {

    }
}

}

