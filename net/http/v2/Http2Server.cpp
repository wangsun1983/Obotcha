#include "Http2Server.hpp"
#include "SocketBuilder.hpp"
#include "Log.hpp"
#include "Http2SettingFrame.hpp"
#include "HttpPacketWriterImpl.hpp"

#include "ConcurrentHashMap.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

void _Http2Server::onSocketMessage(st(Net)::Event event, Socket r, ByteArray pack) {
    switch (event) {
        case st(Net)::Event::Message: {
            HttpLinker info = mLinkers->get(r);
            if (info == nullptr) {
                LOG(ERROR) << "http linker already removed";
                return;
            }
            
            if (info->pushData(pack) == -1) {
                // some thing may be wrong(overflow)
                LOG(ERROR) << "push http data error";
                mHttpListener->onHttpMessage(st(Net)::Event::InternalError, info,
                                            nullptr, nullptr);
                mLinkers->remove(r);
                r->close();
                return;
            }

            ArrayList<HttpPacket> packets = info->pollPacket();
            if(packets == nullptr||packets->size() == 0) {
                return;
            }
            auto iterator = packets->getIterator();
            while(iterator->hasValue()) {
                HttpPacket p = iterator->getValue();
                Http2Packet p2 = Cast<Http2Packet>(p);
                printf("p2 stream id is %d \n",p2->getStreamId());
                Http2Stream stream = info->getStreamController()->getStream(p2->getStreamId());
                if(stream == nullptr) {
                    printf("stream is nullptr!!!! \n");
                }
                Http2ResponseWriter writer = createHttp2ResponseWriter(stream);
                mHttpListener->onHttpMessage(st(Net)::Event::Message, info,writer, p2);
                iterator->next();
            }

            //info->getStreamController->postProcessing(packets);
            
            break;
        }    

        case st(Net)::Event::Connect: {
            HttpLinker info = createHttpLinker(r,mOption->getProtocol());
            mLinkers->put(info->mSocket,info);
            mHttpListener->onHttpMessage(event, info, nullptr, nullptr);
            break;
        }

        case st(Net)::Event::Disconnect: {
            HttpLinker info = mLinkers->get(r);
            mHttpListener->onHttpMessage(event, info, nullptr, nullptr);
            mLinkers->remove(r);
            break;
        }

        default:
            LOG(ERROR)<<"Http2Server onSocketMessage,unSupport event:"<<static_cast<int>(event);
        break;
    }
}


_Http2Server::_Http2Server(InetAddress addr,Http2Listener l,HttpOption option):
                            mHttpListener(l),mAddress(addr),mOption(option) {
}

void _Http2Server::start() {
    if(mOption!= nullptr && mOption->getSSLCertificatePath() != nullptr) {
        mServerSock = createSocketBuilder()
                        ->setOption(mOption)
                        ->setAddress(mAddress)
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

    int threadsNum = st(Http)::Config::kServerThreadNum;

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

    ForEveryOne(client,mLinkers) {
        client->getValue()->close();
    }
    mLinkers->clear();
}

_Http2Server::~_Http2Server() { 
    close(); 
}

} // namespace obotcha
