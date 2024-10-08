#include "HttpServer.hpp"
#include "ArrayList.hpp"
#include "Socket.hpp"
#include "HttpLinker.hpp"
#include "Log.hpp"
#include "SocketBuilder.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

void _HttpServer::onSocketMessage(st(Net)::Event event, Socket sock, ByteArray pack) {
    switch (event) {
        case st(Net)::Event::Message: {
            HttpLinker info = mLinkers->get(sock);
            if (info == nullptr) {
                LOG(ERROR) << "http linker already removed,fail to get message";
                return;
            }

            if (info->pushData(pack) == -1) {
                // some thing may be wrong(overflow)
                LOG(ERROR) << "push http data error";
                mHttpListener->onHttpMessage(st(Net)::Event::InternalError, info,
                                            nullptr, nullptr);
                mLinkers->remove(info->mSocket);
                sock->close();
                return;
            }

            ArrayList<HttpPacket> packets = info->pollPacket();
            if (packets != nullptr && packets->size() != 0) {
                ArrayListIterator<HttpPacket> iterator = packets->getIterator();
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

        case st(Net)::Event::Connect: {
            HttpLinker info = HttpLinker::New(sock,mProtocol);
            mLinkers->put(info->mSocket,info);
            mHttpListener->onHttpMessage(event, info, nullptr, nullptr);
            break;
        }

        case st(Net)::Event::Disconnect: {
            HttpLinker info = mLinkers->get(sock);
            if (info == nullptr) {
                LOG(ERROR) << "http linker already removed,fail to disconnect";
                return;
            }
            mHttpListener->onHttpMessage(event, info, nullptr, nullptr);
            mLinkers->remove(sock);
            break;
        }

        default:
            LOG(ERROR)<<"HttpServer onSocketMessage unknow event:"<<static_cast<int>(event);
        break;
    }
}

_HttpServer::_HttpServer(InetAddress addr, HttpListener l, HttpOption option):
                                                        mHttpListener(l),
                                                        mAddress(addr),
                                                        mOption(option) {
}

int _HttpServer::start() {
    auto builder = SocketBuilder::New();
    builder->setOption(mOption)->setAddress(mAddress);
    
    if(mOption!= nullptr && mOption->getSSLCertificatePath() != nullptr) {
        mProtocol = st(Net)::Protocol::Https;
        mServerSock = builder->newSSLServerSocket();
    } else {
        mServerSock = builder->newServerSocket();
    }
    
    // while(mServerSock->bind() < 0) {
    //     LOG(ERROR) << "bind socket failed,reason " << CurrentError<<";port is "<<mAddress->getPort();
    //     st(Thread)::Sleep(100);
    // }
    //do not retry,return fail direct
    if (mServerSock->bind() < 0) {
        LOG(ERROR) << "bind socket failed,reason " << CurrentError<<";port is "<<mAddress->getPort();
        return -1;
    }

    int threadsNum = st(Http)::Config::kServerThreadNum;
    mSockMonitor = SocketMonitor::New(threadsNum);
    return mSockMonitor->bind(mServerSock, AutoClone(this));
}

// interface for websocket
void _HttpServer::remove(HttpLinker linker) { 
    mSockMonitor->unbind(linker->mSocket,false);
    mLinkers->remove(linker->mSocket);
}

void _HttpServer::close() {
    Inspect(mExitLatch->getCount() <= 0)

    //Do not set instance to null for the following issue:
    //Thread A:                     close HttServer
    //Thread B(SocketMonitor):      one client is disconnected
    //                            ->use linkermanager to find callback
    if(mSockMonitor != nullptr) {
        mSockMonitor->close();
        mSockMonitor->waitForExit();
    }
    
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
