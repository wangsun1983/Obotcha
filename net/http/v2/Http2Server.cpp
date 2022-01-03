#include "Http2Server.hpp"
#include "SocketBuilder.hpp"
#include "Log.hpp"
#include "Http2SettingFrame.hpp"
#include "HttpPacketWriterImpl.hpp"
#include "NetEvent.hpp"

namespace obotcha {

void _Http2Server::onSocketMessage(int event, Socket r, ByteArray pack) {
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
            if(packets == nullptr||packets->size() == 0) {
                return;
            }

            auto iterator = packets->getIterator();
            while(iterator->hasValue()) {
                HttpPacket p = iterator->getValue();
                Http2Packet p2 = Cast<Http2Packet>(p);

                Http2Stream stream = info->getStreamController()->getStream(p2->getStreamId());
                Http2ResponseWriter writer = createHttp2ResponseWriter(stream);

                mHttpListener->onHttpMessage(st(NetEvent)::Message, info,writer, p2);
                iterator->next();
            }
            
            break;
        }    

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


_Http2Server::_Http2Server(InetAddress addr,Http2Listener l,HttpOption option) {
    mHttpListener = l;
    mServerSock = nullptr;
    mSockMonitor = nullptr;
    mAddress = addr;
    mOption = option;
    mLinkerManager = createHttpLinkerManager();
}

void _Http2Server::start() {
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
}

void _Http2Server::close() {
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

_Http2Server::~_Http2Server() { 
    close(); 
}

} // namespace obotcha
