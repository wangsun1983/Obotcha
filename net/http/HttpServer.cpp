#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ArrayList.hpp"
#include "AutoLock.hpp"
#include "Error.hpp"
#include "HttpHeader.hpp"
#include "HttpInternalException.hpp"
#include "HttpLinker.hpp"
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
#include "ForEveryOne.hpp"

namespace obotcha {

void _HttpServer::onSocketMessage(int event, Socket r, ByteArray pack) {
    switch (event) {
        case st(NetEvent)::Message: {
            //HttpLinker info = mLinkerManager->get(r);
            HttpLinker info = mLinkers->get(r);
            if (info == nullptr) {
                LOG(ERROR) << "http linker already removed,fail to get message";
                return;
            }

            if (info->pushData(pack) == -1) {
                // some thing may be wrong(overflow)
                LOG(ERROR) << "push http data error";
                mHttpListener->onHttpMessage(st(NetEvent)::InternalError, info,
                                            nullptr, nullptr);
                //mLinkerManager->remove(info);
                mLinkers->remove(info->mSocket);
                r->close();
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
            HttpLinker info = createHttpLinker(r,mOption->getProtocol());
            //mLinkerManager->add(info);
            mLinkers->put(info->mSocket,info);
            mHttpListener->onHttpMessage(event, info, nullptr, nullptr);
            break;
        }

        case st(NetEvent)::Disconnect: {
            //HttpLinker info = mLinkerManager->get(r);
            HttpLinker info = mLinkers->get(r);
            if (info == nullptr) {
                LOG(ERROR) << "http linker already removed,fail to disconnect";
                return;
            }
            mHttpListener->onHttpMessage(event, info, nullptr, nullptr);
            //mLinkerManager->remove(r);
            mLinkers->remove(r);
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
    //mLinkerManager = createHttpLinkerManager();
    mLinkers = createConcurrentHashMap<Socket,HttpLinker>();
    mExitLatch = createCountDownLatch(1);
}

int _HttpServer::start() {
    auto builder = createSocketBuilder();
    builder->setOption(mOption)->setAddress(mAddress);

    if(mOption->getSSLCertificatePath() != nullptr) {
        mServerSock = builder->newSSLServerSocket();
    } else {
        mServerSock = builder->newServerSocket();
    }
    
    while(mServerSock->bind() < 0) {
        LOG(ERROR) << "bind socket failed,reason " << CurrentError<<";port is "<<mAddress->getPort();
        st(Thread)::sleep(1000*1);
    }

    int threadsNum = st(Enviroment)::getInstance()->getInt(
        st(Enviroment)::gHttpServerThreadsNum, 4);
    mSockMonitor = createSocketMonitor(threadsNum);
    mSockMonitor->bind(mServerSock, AutoClone(this));

    return 0;
}

// interface for websocket
void _HttpServer::remove(HttpLinker linker) { 
    mSockMonitor->unbind(linker->mSocket);
    //mLinkerManager->remove(linker);
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
    //mLinkerManager->clear();
    ForEveryOne(client,mLinkers) {
        client->getValue()->close();
    }
    mLinkers->clear();
    mExitLatch->countDown();
}

_HttpServer::~_HttpServer() { 
    close(); 
}

void _HttpServer::join(long interval) {
    mExitLatch->await(interval);
}

} // namespace obotcha
