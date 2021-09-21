#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ArrayList.hpp"
#include "AutoLock.hpp"
#include "Error.hpp"
#include "HttpHeader.hpp"
#include "HttpInternalException.hpp"
#include "HttpLinker.hpp"
#include "HttpLinkerManager.hpp"
#include "HttpPacket.hpp"
#include "HttpResponseWriter.hpp"
#include "HttpServer.hpp"
#include "InetAddress.hpp"
#include "InterruptedException.hpp"
#include "Log.hpp"
#include "SSLManager.hpp"
#include "SocketBuilder.hpp"
#include "SocketOption.hpp"
#include "String.hpp"

namespace obotcha {

void _HttpServer::onSocketMessage(int event, Socket r, ByteArray pack) {
    switch (event) {
    case SocketEvent::Message: {
        HttpLinker info = st(HttpLinkerManager)::getInstance()->getLinker(r);
        if (info == nullptr) {
            LOG(ERROR) << "http linker already removed";
            return;
        }

        if (info->pushHttpData(pack) == -1) {
            // some thing may be wrong(overflow)
            mHttpListener->onHttpMessage(SocketEvent::InternalError, info,
                                         nullptr, nullptr);
            st(HttpLinkerManager)::getInstance()->removeLinker(r);
            r->close();
            return;
        }

        ArrayList<HttpPacket> packets = info->pollHttpPacket();
        if (packets != nullptr && packets->size() != 0) {
            HttpResponseWriter writer =
                createHttpResponseWriter(info->getSocket()->getOutputStream());
            ListIterator<HttpPacket> iterator = packets->getIterator();
            while (iterator->hasValue()) {
                mHttpListener->onHttpMessage(event, info, writer,
                                             iterator->getValue());
                iterator->next();
            }
        }
    } break;

    case SocketEvent::Connect: {
        HttpLinker info = createHttpLinker(r);
        if (isSSl) {
            SSLInfo ssl = st(SSLManager)::getInstance()->get(
                r->getFileDescriptor()->getFd());
            if (info != nullptr) {
                info->setSSLInfo(ssl);
            }
        }
        st(HttpLinkerManager)::getInstance()->addLinker(info);
        mHttpListener->onHttpMessage(event, info, nullptr, nullptr);
    } break;

    case SocketEvent::Disconnect: {
        HttpLinker info = st(HttpLinkerManager)::getInstance()->getLinker(r);
        mHttpListener->onHttpMessage(event, info, nullptr, nullptr);
        st(HttpLinkerManager)::getInstance()->removeLinker(r);
    }
    }
}

_HttpServer::_HttpServer(InetAddress addr, HttpListener l, HttpOption option) {
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

    if (mOption != nullptr) {
        certificate = mOption->getCertificate();
        key = mOption->getKey();
    }

    if (certificate != nullptr && key != nullptr) {
        // https server
        isSSl = true;
        mSSLServer =
            createSSLServer(mAddress->getAddress(), mAddress->getPort(),
                            AutoClone(this), certificate, key);
    } else {
        isSSl = false;
        mServerSock = createSocketBuilder()
                          ->setOption(mOption)
                          ->setAddress(mAddress)
                          ->newServerSocket();

        if (mServerSock->bind() < 0) {
            LOG(ERROR) << "bind socket failed,reason " << strerror(errno);
            this->close();
            return;
        }

        int threadsNum = st(Enviroment)::getInstance()->getInt(
            st(Enviroment)::gHttpServerThreadsNum, 4);
        mSockMonitor = createSocketMonitor(threadsNum);
        mSockMonitor->bind(mServerSock, AutoClone(this));
    }
}

// interface for websocket
void _HttpServer::deMonitor(Socket s) { mSockMonitor->remove(s); }

void _HttpServer::close() {
    if (mSockMonitor != nullptr) {
        mSockMonitor->close();
        mSockMonitor = nullptr;
    }

    if (mServerSock != nullptr) {
        mServerSock->close();
        mServerSock = nullptr;
    }

    if (mSSLServer != nullptr) {
        mSSLServer->close();
        mSSLServer = nullptr;
    }

    st(HttpLinkerManager)::getInstance()->clear();
}

_HttpServer::~_HttpServer() { close(); }

} // namespace obotcha
