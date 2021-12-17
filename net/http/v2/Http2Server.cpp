#include "Http2Server.hpp"
#include "SocketBuilder.hpp"
#include "Log.hpp"
#include "Http2SettingFrame.hpp"
#include "HttpPacketWriterImpl.hpp"
#include "Http2ShakeHandFrame.hpp"

namespace obotcha {

void _Http2Server::onSocketMessage(int event, Socket r, ByteArray pack) {
    switch (event) {
        case SocketEvent::Message: {
            HttpLinker info = mLinkerManager->getLinker(r);
            ArrayList<HttpPacket> packets = info->pollHttpPacket();
            if(packets == nullptr) {
                return;
            }

            switch(info->getHttp2Status()) {
                case st(HttpPacketParser)::ShakeHand: {
                    HttpPacket packet = packets->get(0);
                    HttpHeader header = packet->getHeader();
                    if(header->getMethod() == st(HttpMethod)::Get
                        && header->getUpgrade()->toString()->equals("h2c")) {
                        //we should decode it's setting frame
                        String settingframe = header->get("http2-settings");
                        printf("settingframe is %s \n",settingframe->toChars());
                        ByteArray data = mBase64->decodeBase64Url(settingframe->toByteArray());
                        data->dump("http settings!!!");
                        //TEST
                        Http2SettingFrame frame = createHttp2SettingFrame();
                        frame->import(data);

                        HttpPacketWriterImpl impl = createHttpPacketWriterImpl(info->getSocket()->getOutputStream());
                        auto shakeHande = createHttp2ShakeHandFrame();
                        impl->write(shakeHande->toShakeHandPacket(st(HttpProtocol)::Http_H2));

                        //response get method
                        info->setHttp2Status(st(HttpPacketParser)::Preface);
                    } else if(header->getMethod() == st(HttpMethod)::Pri 
                        && packet->getEntity()->getContent()->toString()->equalsIgnoreCase("SM")) {
                        info->setHttp2Status(st(HttpPacketParser)::Comunicated);
                        //we should send a http setting frame;
                        Http2SettingFrame ackFrame = createHttp2SettingFrame();
                        info->getSocket()->getOutputStream()->write(ackFrame->toFrameData());
                    }
                }
                break;

                case st(HttpPacketParser)::Preface: {
                    printf("preface!!!!! \n");
                    //no need ack response
                    info->setHttp2Status(st(HttpPacketParser)::Comunicated);
                    //we should send a http setting frame;
                    Http2SettingFrame ackFrame = createHttp2SettingFrame();
                    info->getSocket()->getOutputStream()->write(ackFrame->toFrameData());
                }
                case st(HttpPacketParser)::Comunicated: {
                    printf("i got a communicated message \n");
                    auto iterator = packets->getIterator();
                    while(iterator->hasValue()) {
                        HttpPacket packet = iterator->getValue();
                        /*
                        TODO
                        Http2Frame frame = packet->getFrame();
                        printf("frame type is %d \n",frame->getType());
                        switch(frame->getType()) {
                            case st(Http2Frame)::TypeSettings: {
                                Http2SettingFrame ackFrame = createHttp2SettingFrame();
                                ackFrame->setAck(true);
                                printf("send setting frame ack!!!!!!!!!!!!!!!!!!!!!!!!! \n");
                                info->getSocket()->getOutputStream()->write(ackFrame->toFrameData());
                            }
                            break;
                        }
                        iterator->next();
                         */
                    }
                }
                break;
            }
        }
        break;
        

        case SocketEvent::Connect: {
            HttpLinker info = createHttpLinker(r,mOption->getProtocol());
            mLinkerManager->addLinker(info);
            mHttpListener->onHttpMessage(event, info, nullptr, nullptr);
            break;
        }

        case SocketEvent::Disconnect: {
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
    mBase64 = createBase64();
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
