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
#include "HttpServer.hpp"
#include "InetAddress.hpp"
#include "InterruptedException.hpp"
#include "Log.hpp"
#include "SocketBuilder.hpp"
#include "SocketOption.hpp"
#include "String.hpp"
#include "HttpPacketWriter.hpp"
#include "HttpPacketWriterImpl.hpp"
#include "Base64.hpp"
#include "NetEvent.hpp"

namespace obotcha {

void _HttpServer::onSocketMessage(int event, Socket r, ByteArray pack) {
    switch (event) {
        case st(NetEvent)::Message: {
            HttpLinker info = mLinkerManager->getLinker(r);
            if (info == nullptr) {
                LOG(ERROR) << "http linker already removed";
                return;
            }

            if (info->pushHttpData(pack) == -1) {
                // some thing may be wrong(overflow)
                LOG(ERROR) << "push http data error";
                mHttpListener->onHttpMessage(st(NetEvent)::InternalError, info,
                                            nullptr, nullptr);
                mLinkerManager->removeLinker(r);
                r->close();
                return;
            }

            ArrayList<HttpPacket> packets = info->pollHttpPacket();
            if (packets != nullptr && packets->size() != 0) {
                ListIterator<HttpPacket> iterator = packets->getIterator();
                while (iterator->hasValue()) {
                    mHttpListener->onHttpMessage(event, info, info->getWriter(),
                                                iterator->getValue());
                    iterator->next();
                }
            }
        }
        break;

        case st(NetEvent)::Connect: {
            HttpLinker info = createHttpLinker(r,mOption->getProtocol());
            mLinkerManager->addLinker(info);
            mHttpListener->onHttpMessage(event, info, nullptr, nullptr);
            break;
        }

        case st(NetEvent)::Disconnect: {
            HttpLinker info = mLinkerManager->getLinker(r);
            mHttpListener->onHttpMessage(event, info, nullptr, nullptr);
            mLinkerManager->removeLinker(r);
            break;
        }
    }
}

_HttpServer::_HttpServer(InetAddress addr, HttpListener l, HttpOption option) {
    mHttpListener = l;
    mServerSock = nullptr;
    mSockMonitor = nullptr;
    mAddress = addr;
    mOption = option;
    mLinkerManager = createHttpLinkerManager();
}

void _HttpServer::start() {
    String certificate = nullptr;
    String key = nullptr;

    if (mOption != nullptr) {
        certificate = mOption->getCertificate();
        key = mOption->getKey();
    }

    if(certificate != nullptr && key != nullptr) {
        mServerSock = createSocketBuilder()
                        ->setOption(mOption)
                        ->setAddress(mAddress)
                        ->setSSLCretificatePath(certificate)
                        ->setSSLKeyPath(key)
                        ->newSSLServerSocket();
    } else {
        mServerSock = createSocketBuilder()
                        ->setOption(mOption)
                        ->setAddress(mAddress)
                        ->newServerSocket();
    }
    

    if (mServerSock->bind() < 0) {
        LOG(ERROR) << "bind socket failed,reason " << strerror(errno);
        this->close();
        return;
    }

    int threadsNum = st(Enviroment)::getInstance()->getInt(
        st(Enviroment)::gHttpServerThreadsNum, 4);
    mSockMonitor = createSocketMonitor(threadsNum);
    mSockMonitor->bind(mServerSock, AutoClone(this));
    //}
}

// interface for websocket
void _HttpServer::deMonitor(Socket s) { 
    mSockMonitor->remove(s); 
}

void _HttpServer::close() {
    if (mSockMonitor != nullptr) {
        mSockMonitor->close();
        mSockMonitor = nullptr;
    }

    if (mServerSock != nullptr) {
        mServerSock->close();
        mServerSock = nullptr;
    }

    if(mLinkerManager != nullptr) {
        mLinkerManager->clear();
        mLinkerManager = nullptr;
    }
}

_HttpServer::~_HttpServer() { 
    close(); 
}

} // namespace obotcha
