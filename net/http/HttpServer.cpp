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

namespace obotcha {

void _HttpServer::onSocketMessage(int event,Socket r,ByteArray pack) {
    switch(event) {
        case st(HttpListener)::Message: {
            printf("_HttpServer::onDataReceived \n");
            HttpClientInfo info = st(HttpClientManager)::getInstance()->getClientInfo(r);
            if(info == nullptr) {
                return;
            }
            info->pushHttpData(pack);
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

        case st(HttpListener)::Connect:{
            HttpClientInfo info = createHttpClientInfo(r);

            //TODO
            SSLInfo ssl = st(SSLManager)::getInstance()->get(r->getFd());
            if(info != nullptr) {
                info->setSSLInfo(ssl);
            }
            st(HttpClientManager)::getInstance()->addClientInfo(info);
            mSockMonitor->bind(r->getFd(),AutoClone(this));
            mHttpListener->onHttpMessage(event,info,nullptr,nullptr);
        }
        break;

        case st(HttpListener)::Disconnect: {
            HttpClientInfo info = st(HttpClientManager)::getInstance()->getClientInfo(r);
            mHttpListener->onHttpMessage(event,info,nullptr,nullptr);
            mSockMonitor->remove(r);
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

    if(mOption != nullptr) {
        certificate = mOption->getCertificate();
        key = mOption->getKey();
    }

    if(certificate != nullptr && key != nullptr) {
        //https server
        mSSLServer = createSSLServer(mAddress->getAddress(),mAddress->getPort(),AutoClone(this),certificate,key);
    } else {
        SocketOption option = createSocketOption();
        int sendtimeout = mOption->getSendTimeout();
        int rcvtimeout = mOption->getRcvTimeout();

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
        printf("http server trace1 \n");
        int threadsNum = st(Enviroment)::getInstance()->getInt(st(Enviroment)::gHttpServerThreadsNum,4);
        mSockMonitor = createSocketMonitor(threadsNum);
        printf("http server trace2 \n");
        mSockMonitor->bind(mServerSock,AutoClone(this));
        printf("http server trace3 \n");
        
    }
}

//interface for websocket
void _HttpServer::deMonitor(Socket s) {
    mSockMonitor->remove(s);
}

void _HttpServer::exit() {
    if(mSockMonitor != nullptr) {
        mSockMonitor->release();
    }

    if(mServerSock != nullptr) {
        mServerSock->close();
    }

    if(mSSLServer != nullptr) {
        mSSLServer->release();
    }

    st(HttpClientManager)::getInstance()->clear();
}

}

