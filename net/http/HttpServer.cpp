#include "HttpServer.hpp"
#include "ArrayList.hpp"
#include "Enviroment.hpp"
#include "AutoLock.hpp"
#include "Socket.hpp"
#include "HttpLinker.hpp"
#include "Log.hpp"
#include "SocketBuilder.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

void _HttpServer::onSocketMessage(int event, Socket sock, ByteArray pack) {
    switch (event) {
        case st(NetEvent)::Message: {
            HttpLinker info = mLinkers->get(sock);
            if (info == nullptr) {
                LOG(ERROR) << "http linker already removed,fail to get message";
                return;
            }

            if (info->pushData(pack) == -1) {
                // some thing may be wrong(overflow)
                LOG(ERROR) << "push http data error";
                mHttpListener->onHttpMessage(st(NetEvent)::InternalError, info,
                                            nullptr, nullptr);
                mLinkers->remove(info->mSocket);
                sock->close();
                return;
            }

            ArrayList<HttpPacket> packets = info->pollPacket();
            if (packets != nullptr && packets->size() != 0) {
                ListIterator<HttpPacket> iterator = packets->getIterator();
                while (iterator->hasValue()) {
                    HttpPacket p = iterator->getValue();
                    HttpHeaderVersion v = p->getHeader()->getVersion();
                    HttpPacketWriter w = nullptr;
                    if(v->getMajorVer() == 0 && v->getMinorVer() == 9) {
                        w = info->getSimpleWriter();
                    } else {
                        w = info->getWriter();
                    }
                    mHttpListener->onHttpMessage(event, info, w,p);
                    iterator->next();
                }
            }
            break;
        }

        case st(NetEvent)::Connect: {
            //TODO whether we should chekc it’s session
            HttpLinker info = createHttpLinker(sock,mProtocol);
            mLinkers->put(info->mSocket,info);
            mHttpListener->onHttpMessage(event, info, nullptr, nullptr);
            break;
        }

        case st(NetEvent)::Disconnect: {
            HttpLinker info = mLinkers->get(sock);
            if (info == nullptr) {
                LOG(ERROR) << "http linker already removed,fail to disconnect";
                return;
            }
            mHttpListener->onHttpMessage(event, info, nullptr, nullptr);
            mLinkers->remove(sock);
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
    mProtocol = st(NetProtocol)::Http;
    mLinkers = createConcurrentHashMap<Socket,HttpLinker>();
    mExitLatch = createCountDownLatch(1);
}

int _HttpServer::start() {
    auto builder = createSocketBuilder();
    builder->setOption(mOption)->setAddress(mAddress);
    
    if(mOption!= nullptr && mOption->getSSLCertificatePath() != nullptr) {
        mProtocol = st(NetProtocol)::Https;
        mServerSock = builder->newSSLServerSocket();
    } else {
        mServerSock = builder->newServerSocket();
    }
    
    while(mServerSock->bind() < 0) {
        LOG(ERROR) << "bind socket failed,reason " << CurrentError<<";port is "<<mAddress->getPort();
        st(Thread)::sleep(100);
    }

    int threadsNum = st(Enviroment)::getInstance()->getInt(
        st(Enviroment)::gHttpServerThreadsNum, 4);
    mSockMonitor = createSocketMonitor(threadsNum);

    return mSockMonitor->bind(mServerSock, AutoClone(this));
}

// interface for websocket
void _HttpServer::remove(HttpLinker linker) { 
    mSockMonitor->unbind(linker->mSocket,false);
    mLinkers->remove(linker->mSocket);
}

void _HttpServer::close() {
    Inspect(mExitLatch->getCount() <= 0);

    //Do not set instance to null for the following issue:
    //Thread A:                     close HttServer
    //Thread B(SocketMonitor):      one client is disconnected
    //                            ->use linkermanager to find callback
    mSockMonitor->close();
    mServerSock->close();
    ForEveryOne(client,mLinkers) {
        client->getValue()->close();
    }
    mLinkers->clear();
    mExitLatch->countDown();
}

_HttpServer::~_HttpServer() { 
    close(); 
    waitForExit(1000);
}

void _HttpServer::waitForExit(long interval) {
    mExitLatch->await(interval);
}

} // namespace obotcha
